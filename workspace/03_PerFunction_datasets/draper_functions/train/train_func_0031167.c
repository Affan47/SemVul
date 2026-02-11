gl5_text_get(void *data, Evas_Object *obj __UNUSED__, const char *part)
{
   const Testitem *tit = data;
   char buf[256];
   if (!strcmp(part, "elm.text"))
     {
        snprintf(buf, sizeof(buf), "Item mode %i", tit->mode);
     }
   else if (!strcmp(part, "elm.text.sub"))
     {
        snprintf(buf, sizeof(buf), "%i bottles on the wall", tit->mode);
     }
   return strdup(buf);
}
