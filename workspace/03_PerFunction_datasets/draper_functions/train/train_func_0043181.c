_evas_cache_image_lru_add(Image_Entry *im)
{
   if (im->flags.lru) return;
   _evas_cache_image_dirty_del(im);
   _evas_cache_image_activ_del(im);
   _evas_cache_image_lru_nodata_del(im);
   if (!im->cache_key) return;
   im->flags.lru = 1;
   im->flags.cached = 1;
   eina_hash_direct_add(im->cache->inactiv, im->cache_key, im);
   im->cache->lru = eina_inlist_prepend(im->cache->lru, EINA_INLIST_GET(im));
   im->cache->usage += im->cache->func.mem_size_get(im);
}
