WriteInputDeckSummary( const char* fname )
{
  ofstream xmlSummary( fname, ios::out | ios::trunc );
  if ( ! xmlSummary.good() )
    {
    return 1;
    }

  xmlSummary
    << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl
    << "<lsdyna>" << endl;

  std::string dbDir = this->P->Fam.GetDatabaseDirectory();
  std::string dbName = this->P->Fam.GetDatabaseBaseName();
  if ( this->IsDatabaseValid() && ! dbDir.empty() && ! dbName.empty() )
    {
#ifndef WIN32
    if ( dbDir[0] == '/' )
#else
    if ( dbDir[0] == '\\' )
#endif
      {

      xmlSummary
        << "  <database path=\"" << dbDir.c_str()
        << "\" name=\"" << dbName.c_str() << "\"/>" << endl;
      }
    }

  for ( unsigned p = 0; p < this->P->PartNames.size(); ++p )
    {
    xmlSummary
      << "  <part id=\"" << this->P->PartIds[p]
      << "\" material_id=\"" << this->P->PartMaterials[p]
      << "\" status=\"" << this->P->PartStatus[p]
      << "\"><name>" << this->P->PartNames[p].c_str()
      << "</name></part>" << endl;
    }

  xmlSummary
    << "</lsdyna>" << endl;

  return 0;
}
