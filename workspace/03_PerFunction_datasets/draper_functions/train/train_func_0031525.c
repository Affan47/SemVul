_fi_FindFirstFile(const char* lpFileName, _fi_find_data* lpFindFileData)
{
   _fi_find_handle dat = new _fi_priv_data(lpFileName);

   DIR* h = opendir(dat->root);
   dat->d = h;
   if(h != 0)
   {
      if(_fi_FindNextFile(dat, lpFindFileData))
         return dat;
      closedir(h);
   }
   delete dat;
   return 0;
}
