trans_alloc(void) {

   uint32 size, target;


   target = option_get_int("Hash");

   if (target < 4) target = 16;
   if (target > 1024) target = 1024;

   target *= 1024 * 1024;

   for (size = 1; size != 0 && size <= target; size *= 2);

   size /= 2;
   ASSERT(size>0&&size<=target);


   size /= sizeof(entry_t);
   ASSERT(size!=0&&(size&(size-1))==0);

   Trans->size = size + (ClusterSize - 1);
   Trans->mask = size - 1;

   Trans->table = (entry_t *) my_malloc(Trans->size*sizeof(entry_t));

   trans_clear();

   ASSERT(trans_is_ok());
}
