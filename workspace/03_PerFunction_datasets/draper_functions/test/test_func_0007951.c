evas_font_desc_unref(Evas_Font_Description *fdesc)
{
   if (--(fdesc->ref) == 0)
     {
        eina_stringshare_del(fdesc->name);
        eina_stringshare_del(fdesc->fallbacks);
        eina_stringshare_del(fdesc->lang);
        free(fdesc);
     }
}
