_eina_file_real_close(Eina_File *file)
{
   if (file->refcount != 0) return;

   eina_hash_free(file->rmap);
   eina_hash_free(file->map);

   if (file->global_map != MAP_FAILED)
     munmap(file->global_map, file->length);

   close(file->fd);

   free(file);
}
