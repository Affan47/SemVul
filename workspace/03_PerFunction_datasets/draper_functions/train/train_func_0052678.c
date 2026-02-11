intel_miptree_unmap_blit(struct intel_context *intel,
			 struct intel_mipmap_tree *mt,
			 struct intel_miptree_map *map,
			 unsigned int level,
			 unsigned int slice)
{
   struct gl_context *ctx = &intel->ctx;

   intel_miptree_unmap_raw(intel, map->mt);

   if (map->mode & GL_MAP_WRITE_BIT) {
      bool ok = intel_miptree_blit(intel,
                                   map->mt, 0, 0,
                                   0, 0, false,
                                   mt, level, slice,
                                   map->x, map->y, false,
                                   map->w, map->h, GL_COPY);
      WARN_ONCE(!ok, "Failed to blit from linear temporary mapping");
   }

   intel_miptree_release(&map->mt);
}
