dev_lookup(vm_instance_t *vm,m_uint64_t phys_addr,int cached)
{
   struct vdevice *dev;

   if (!vm)
      return NULL;

   for(dev=vm->dev_list;dev;dev=dev->next) {
      if (cached && !(dev->flags & VDEVICE_FLAG_CACHING))
         continue;

      if ((phys_addr >= dev->phys_addr) &&
          ((phys_addr - dev->phys_addr) < dev->phys_len))
         return dev;
   }

   return NULL;
}
