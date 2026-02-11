cso_cache_delete(struct cso_cache *sc)
{
   int i;
   assert(sc);

   if (!sc)
      return;


   cso_for_each_state(sc, CSO_BLEND, delete_blend_state, 0);
   cso_for_each_state(sc, CSO_DEPTH_STENCIL_ALPHA, delete_depth_stencil_state, 0);
   cso_for_each_state(sc, CSO_RASTERIZER, delete_rasterizer_state, 0);
   cso_for_each_state(sc, CSO_SAMPLER, delete_sampler_state, 0);
   cso_for_each_state(sc, CSO_VELEMENTS, delete_velements, 0);

   for (i = 0; i < CSO_CACHE_MAX; i++)
      cso_hash_delete(sc->hashes[i]);

   FREE(sc);
}
