clipped_header(Clipped o, struct how *h)
{
   Object subo;
   char *name;


   if(DXGetStringAttribute((Object)o,"name",&name)){
      pstring(h->dfp,0,0,0,name);
      fprintf(h->dfp,", ");
   }
   fprintf(h->dfp,"clipped object,");
   DXGetClippedInfo(o,&subo,NULL);
   if (!object_header((Object)subo,h))
      return ERROR;

   return OK;
}
