destroy()
   {
   Mutex_Holder lock(mutex);

   blocks.clear();

   for(u32bit j = 0; j != allocated.size(); ++j)
      dealloc_block(allocated[j].first, allocated[j].second);
   allocated.clear();
   }
