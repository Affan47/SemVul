nouveau_chipset(int fd)
{
   struct drm_nouveau_getparam gp = { NOUVEAU_GETPARAM_CHIPSET_ID, 0 };
   int ret;

   ret = drmCommandWriteRead(fd, DRM_NOUVEAU_GETPARAM, &gp, sizeof(gp));
   if (ret)
      return -1;

   return gp.value;
}
