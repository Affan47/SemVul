intel_miptree_map_blit(struct brw_context *brw,
		       struct intel_mipmap_tree *mt,
		       struct intel_miptree_map *map,
		       unsigned int level, unsigned int slice)
{
   map->mt = intel_miptree_create(brw, GL_TEXTURE_2D, mt->format,
                                  0, 0,
                                  map->w, map->h, 1,
                                  false, 0,
                                  INTEL_MIPTREE_TILING_NONE);
   if (!map->mt) {
      fprintf(stderr, "Failed to allocate blit temporary\n");
      goto fail;
   }
   map->stride = map->mt->region->pitch;

   if (!intel_miptree_blit(brw,
                           mt, level, slice,
                           map->x, map->y, false,
                           map->mt, 0, 0,
                           0, 0, false,
                           map->w, map->h, GL_COPY)) {
      fprintf(stderr, "Failed to blit\n");
      goto fail;
   }

   map->ptr = intel_miptree_map_raw(brw, map->mt);

   DBG("%s: %d,%d %dx%d from mt %p (%s) %d,%d = %p/%d\n", __FUNCTION__,
       map->x, map->y, map->w, map->h,
       mt, _mesa_get_format_name(mt->format),
       level, slice, map->ptr, map->stride);

   return;

fail:
   intel_miptree_release(&map->mt);
   map->ptr = NULL;
   map->stride = 0;
}
