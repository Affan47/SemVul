DoItem(Item &Itm,int &Fd)
{
   if (Itm.Type != Item::File)
      return true;


   for (char *I = Itm.Name; *I != 0; I++)
      if (*I == '/')
	 *I = '_';


   Itm.UID = 0;
   Itm.GID = 0;
   Itm.Mode &= ~(S_IWGRP | S_IWOTH);

   return pkgDirStream::DoItem(Itm,Fd);
}
