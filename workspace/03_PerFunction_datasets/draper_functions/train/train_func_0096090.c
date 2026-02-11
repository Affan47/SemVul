_eina_file_map_rule_apply(Eina_File_Populate rule, void *addr, unsigned long int size, Eina_Bool hugetlb)
{
   int tmp = 42;
   int flag = MADV_RANDOM;

   switch (rule)
     {
      case EINA_FILE_RANDOM: flag = MADV_RANDOM; break;
      case EINA_FILE_SEQUENTIAL: flag = MADV_SEQUENTIAL; break;
      case EINA_FILE_POPULATE: flag = MADV_WILLNEED; break;
      case EINA_FILE_WILLNEED: flag = MADV_WILLNEED; break;
     }

   madvise(addr, size, flag);

#ifndef MAP_POPULATE
   if (rule == EINA_FILE_POPULATE)
     tmp ^= _eina_file_map_populate(addr, size, hugetlb);
#else
   (void) hugetlb;
#endif

   return tmp;
}
