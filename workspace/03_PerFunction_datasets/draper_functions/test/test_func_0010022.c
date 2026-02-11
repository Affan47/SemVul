eina_file_close(Eina_File *file)
{
   Eina_Bool leave = EINA_TRUE;

   EINA_SAFETY_ON_NULL_RETURN(file);

   eina_lock_take(&_eina_file_lock_cache);

   eina_lock_take(&file->lock);
   file->refcount--;
   if (file->refcount == 0) leave = EINA_FALSE;
   eina_lock_release(&file->lock);
   if (leave) goto end;

   if (eina_hash_find(_eina_file_cache, file->filename) == file)
     eina_hash_del(_eina_file_cache, file->filename, file);
   _eina_file_real_close(file);

 end:
   eina_lock_release(&_eina_file_lock_cache);
}
