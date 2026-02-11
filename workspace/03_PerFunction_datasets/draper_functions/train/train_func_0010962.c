sge_filecmp(const char *name0, const char *name1)
{
   SGE_STRUCT_STAT buf0, buf1;

   DENTER(TOP_LAYER, "filecmp");

   if (!strcmp(name0, name1)) {
      DEXIT;
      return 0;
   }

   if (SGE_STAT(name0, &buf0)<0) {
      DEXIT;
      return 1;
   }

   if (SGE_STAT(name1, &buf1)<0) {
      DEXIT;
      return 1;
   }

   if (buf0.st_ino == buf1.st_ino && buf0.st_dev == buf1.st_dev) {
      DEXIT;
      return 0;
   } else {
      DEXIT;
      return 1;
   }
}
