_file_trash_action(Evry_Action *act)
{
   Efreet_Uri *euri;
   int ok = 0;
   int force = (EVRY_ITEM_DATA_INT_GET(act) == ACT_DELETE);

   GET_FILE(file, act->it1.item);

   if (!(evry->file_url_get(file)))
     return 0;

   euri = efreet_uri_decode(file->url);

   if (euri)
     {
        ok = efreet_trash_delete_uri(euri, force);
        efreet_uri_free(euri);
     }

   return ok > 0;
}
