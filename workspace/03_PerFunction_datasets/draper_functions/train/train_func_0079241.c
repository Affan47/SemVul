e_fm2_path_get(Evas_Object *obj, const char **dev, const char **path)
{
   if (dev) *dev = NULL;
   if (path) *path = NULL;
   EFM_SMART_CHECK();
   if (dev) *dev = sd->dev;
   if (path) *path = sd->path;
}
