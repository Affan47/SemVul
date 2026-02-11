unregister_surface(struct set_entry *entry)
{
   struct vdp_surface *surf = (struct vdp_surface *)entry->key;
   GET_CURRENT_CONTEXT(ctx);

   if (surf->state == GL_SURFACE_MAPPED_NV) {
      GLintptr surfaces[] = { (GLintptr)surf };
      _mesa_VDPAUUnmapSurfacesNV(1, surfaces);
   }

   _mesa_set_remove(ctx->vdpSurfaces, entry);
   FREE(surf);
}
