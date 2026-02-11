dev_get_by_name(vm_instance_t *vm,char *name)
{
   struct vdevice *dev;

   if (!vm)
      return NULL;

   for(dev=vm->dev_list;dev;dev=dev->next)
      if (!strcmp(dev->name,name))
         return dev;

   return NULL;
}
