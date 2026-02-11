sge_is_executable(const char *name)
{
   SGE_STRUCT_STAT stat_buffer;
   int ret = SGE_STAT(name, &stat_buffer);
   if (!ret) {
      return (int)(stat_buffer.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH));
   } else {
      return 0;
   }
}
