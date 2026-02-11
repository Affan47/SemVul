elm_config_cache_edje_collection_cache_size_set(int size)
{
   if (_elm_config->edje_collection_cache == size) return;
   _elm_config->edje_collection_cache = size;

   _elm_recache();
}
