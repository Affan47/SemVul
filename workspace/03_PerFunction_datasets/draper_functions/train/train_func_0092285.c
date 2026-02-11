err_list_free(int list_num)
#endif
{
   if (list_num < 0 || list_num >= err_list_end) return -1;
   if (err_list[list_num].listp != (char **)NULL) {
      err_list[list_num].listp = (char **)NULL;
      err_list[list_num].len = 0;
      err_list[list_num].warn = 0;
   }
   return 0;
}
