dev_ram_ghost_init(vm_instance_t *vm,char *name,int sparse,char *filename,
                       m_uint64_t paddr,m_uint32_t len)
{
   struct ram_data *d;


   if (!filename || !(d = malloc(sizeof(*d)))) {
      vm_error(vm,"RAM_ghost: unable to create device (filename=%s).\n",filename);
      return(-1);
   }

   memset(d,0,sizeof(*d));
   d->delete_file = FALSE;

   if (!(d->filename = strdup(filename)))
      goto err_filename;

   vm_object_init(&d->vm_obj);
   d->vm_obj.name = name;
   d->vm_obj.data = d;
   d->vm_obj.shutdown = (vm_shutdown_t)dev_ram_shutdown;

   if (!(d->dev = dev_create_ghost_ram(vm,name,sparse,d->filename,
                                       paddr,len)))
   {
      vm_error(vm,"RAM_ghost: unable to create device (filename=%s)\n",d->filename);
      goto err_dev_create;
   }

   vm_object_add(vm,&d->vm_obj);
   return(0);

 err_dev_create:
   free(d->filename);
 err_filename:
   free(d);
   return(-1);
}
