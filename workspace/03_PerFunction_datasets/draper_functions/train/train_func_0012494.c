AddInstallRule(
                 std::ostream& os,
                 cmInstallType type,
                 std::vector<std::string> const& files,
                 bool optional ,
                 const char* permissions_file ,
                 const char* permissions_dir ,
                 const char* rename ,
                 const char* literal_args ,
                 Indent const& indent
                 )
{

  std::string stype;
  switch(type)
    {
    case cmInstallType_DIRECTORY:      stype = "DIRECTORY"; break;
    case cmInstallType_PROGRAMS:       stype = "PROGRAM"; break;
    case cmInstallType_EXECUTABLE:     stype = "EXECUTABLE"; break;
    case cmInstallType_STATIC_LIBRARY: stype = "STATIC_LIBRARY"; break;
    case cmInstallType_SHARED_LIBRARY: stype = "SHARED_LIBRARY"; break;
    case cmInstallType_MODULE_LIBRARY: stype = "MODULE"; break;
    case cmInstallType_FILES:          stype = "FILE"; break;
    }
  os << indent;
  std::string dest = this->GetInstallDestination();
  if (cmSystemTools::FileIsFullPath(dest.c_str()))
     {
     os << "list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES\n";
     os << indent << " \"";
     for(std::vector<std::string>::const_iterator fi = files.begin();
               fi != files.end(); ++fi)
             {
               if (fi!=files.begin())
                 {
                 os << ";";
                 }
               os << dest << "/";
               if (rename && *rename)
                 {
                 os << rename;
                 }
               else
                 {
                 os << cmSystemTools::GetFilenameName(*fi);
                 }
             }
     os << "\")\n";
     os << indent << "IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)\n";
     os << indent << indent << "message(WARNING \"ABSOLUTE path INSTALL "
        << "DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}\")\n";
     os << indent << "ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)\n";

     os << indent << "IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)\n";
     os << indent << indent << "message(FATAL_ERROR \"ABSOLUTE path INSTALL "
        << "DESTINATION forbidden (by caller): "
        << "${CMAKE_ABSOLUTE_DESTINATION_FILES}\")\n";
     os << indent << "ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)\n";
     }
  os << "FILE(INSTALL DESTINATION \"" << dest << "\" TYPE " << stype.c_str();
  if(optional)
    {
    os << " OPTIONAL";
    }
  if(permissions_file && *permissions_file)
    {
    os << " PERMISSIONS" << permissions_file;
    }
  if(permissions_dir && *permissions_dir)
    {
    os << " DIR_PERMISSIONS" << permissions_dir;
    }
  if(rename && *rename)
    {
    os << " RENAME \"" << rename << "\"";
    }
  os << " FILES";
  if(files.size() == 1)
    {
    os << " \"" << files[0] << "\"";
    }
  else
    {
    for(std::vector<std::string>::const_iterator fi = files.begin();
        fi != files.end(); ++fi)
      {
      os << "\n" << indent << "  \"" << *fi << "\"";
      }
    os << "\n" << indent << " ";
    if(!(literal_args && *literal_args))
      {
      os << " ";
      }
    }
  if(literal_args && *literal_args)
    {
    os << literal_args;
    }
  os << ")\n";
}
