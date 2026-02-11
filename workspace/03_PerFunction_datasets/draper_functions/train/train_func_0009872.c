_overlay_default_free(Overlay_Default *ovl)
{
   EINA_SAFETY_ON_NULL_RETURN(ovl);

   if (ovl->content) evas_object_del(ovl->content);
   if (ovl->icon) evas_object_del(ovl->icon);
   if (ovl->clas_content) evas_object_del(ovl->clas_content);
   if (ovl->clas_icon) evas_object_del(ovl->clas_icon);
   if (ovl->layout) evas_object_del(ovl->layout);

   free(ovl);
}
