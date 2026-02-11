HTS_feof(HTS_File * fp)
{
   if (fp == NULL) {
      return 1;
   } else if (fp->type == HTS_FILE) {
      return feof((FILE *) fp->pointer);
   } else if (fp->type == HTS_DATA) {
      HTS_Data *d = (HTS_Data *) fp->pointer;
      return d->size <= d->index ? 1 : 0;
   }
   HTS_error(0, "HTS_feof: Unknown file type.\n");
   return 1;
}
