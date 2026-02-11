WantSize()
{
   struct stat st;
   if(!strcmp(session->GetProto(),"file")
   && stat(dir_file(session->GetCwd(),file),&st)!=-1)
      SetSize(st.st_size);
   else
      super::WantSize();
}
