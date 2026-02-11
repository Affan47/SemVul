dev_ram_shutdown(vm_instance_t *vm,struct ram_data *d)
{
   if (d != NULL) {

      dev_remove(vm,d->dev);
      free(d->dev);


      if (d->filename) {
         if (d->delete_file)
            unlink(d->filename);
         free(d->filename);
      }


      free(d);
   }
}
