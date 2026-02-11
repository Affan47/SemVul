_fi_FindNextFile(_fi_find_handle dat, _fi_find_data* lpFindFileData)
{
   dirent* d;
   do
   {
      d = readdir(dat->d);
   } while(d && !iswild(dat->mask, d->d_name));

   if(d)
   {
      std::strcpy(lpFindFileData->cFileName, d->d_name);
      lpFindFileData->dwFileAttributes = _fi_attributes(dat->root, d->d_name);
      return true;
   }
   return false;
}
