dri_device_create(int fd)
{
   struct gbm_dri_device *dri;
   int ret;

   dri = calloc(1, sizeof *dri);
   if (!dri)
      return NULL;

   dri->base.base.fd = fd;
   dri->base.base.bo_create = gbm_dri_bo_create;
   dri->base.base.bo_import = gbm_dri_bo_import;
   dri->base.base.is_format_supported = gbm_dri_is_format_supported;
   dri->base.base.bo_write = gbm_dri_bo_write;
   dri->base.base.bo_destroy = gbm_dri_bo_destroy;
   dri->base.base.destroy = dri_destroy;
   dri->base.base.surface_create = gbm_dri_surface_create;
   dri->base.base.surface_destroy = gbm_dri_surface_destroy;

   dri->base.type = GBM_DRM_DRIVER_TYPE_DRI;
   dri->base.base.name = "drm";

   ret = dri_screen_create(dri);
   if (ret)
      goto err_dri;

   return &dri->base.base;

err_dri:
   free(dri);

   return NULL;
}
