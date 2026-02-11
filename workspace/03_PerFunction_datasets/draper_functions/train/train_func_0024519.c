ExcludeUnaccessible()
{
   for(int i=0; i<fnum; i++)
   {
      if(!(files[i]->defined&FileInfo::MODE) || !(files[i]->defined&FileInfo::TYPE))
	 continue;
      if((files[i]->filetype==FileInfo::NORMAL    && !(files[i]->mode&0444))
      || (files[i]->filetype==FileInfo::DIRECTORY && !(files[i]->mode&0444&(files[i]->mode<<2))))
      {
	 Sub(i);
	 i--;
      }
   }
}
