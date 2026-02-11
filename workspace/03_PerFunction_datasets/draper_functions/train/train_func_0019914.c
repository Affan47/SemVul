get_memory_usage(void) const
{
   unsigned int size=sizeof(*this);
   if (info) size+=info->get_memory_usage();
   if (bg44) size+=bg44->get_memory_usage();
   if (fgjb) size+=fgjb->get_memory_usage();
   if (fgpm) size+=fgpm->get_memory_usage();
   if (fgbc) size+=fgbc->size()*sizeof(int);
   if (anno) size+=anno->size();
   if (meta) size+=meta->size();
   if (dir) size+=dir->get_memory_usage();
   return size;
}
