LoadFileInCWD(int filenumber)
{
   uint8_t buf[FAT_HARDSECT];
   FAT_DIRECTORY *pde = (FAT_DIRECTORY *)buf;
   int i, j, fn, sector, cluster, cluster_cnt;
   int de_per_sector = FAT_HARDSECT/sizeof(FAT_DIRECTORY);
   uint8_t c;

   sector = filenumber / de_per_sector;
   fn = filenumber - (sector * de_per_sector);

   if (cwd.StartCluster)
   {


      cluster = cwd.StartCluster;
      cluster_cnt = sector / bpb.SectorsPerCluster;
      for (i=0; i<cluster_cnt && cluster<0xfff7 && cluster; i++)
         cluster = GetNextCluster(cluster);
      if (cluster >= 0xfff7 || cluster == 0)
         return FAT_END_OF_DIR;
      cwd.CurrSector = ConvertClusterToSector(cluster);
      sector -= cluster_cnt * bpb.SectorsPerCluster;
   }
   else
   {
      cwd.CurrSector = cwd.StartSector;


      if (filenumber > (da.RootDirNumSectors * de_per_sector))
         return FAT_END_OF_DIR;
   }

   cwd.CurrSector += sector;

   fa.DirEntryNum = fn;
   fa.DirSectorNum = cwd.CurrSector;


   pde += fn;
   pde->Name[0] = 0;
   readsect(fa.DirSectorNum, 1, buf, sizeof(buf));

   c = pde->Name[0];
   if (c == 0x0)
      return FAT_END_OF_DIR;
   if (c == FAT_FILE_DELETED)
      return FAT_FILE_DELETED;


   for (i=0; (i<sizeof(pde->Name)) && pde->Name[i] && (pde->Name[i] != ' '); i++)
      fa.Name[i] = pde->Name[i];
   if (pde->Ext[0] && (pde->Ext[0] != ' '))
   {
      fa.Name[i++] = '.';
      for (j=0; (pde->Ext[j] != ' ') && (j<sizeof(pde->Ext)); j++, i++)
         fa.Name[i] = pde->Ext[j];
   }

   fa.Name[i] = 0;

   fa.Attr =  pde->Attributes;

   if (pde->Attributes == 0xf)
   {
      return FAT_LONG_FILENAME;
   }

   fa.StartCluster = pde->StartCluster;
   fa.CurrCluster = fa.StartCluster;
   fa.Size = pde->Size;
   fa.CurrSectorNumInCluster = 0;

   return 0;
}
