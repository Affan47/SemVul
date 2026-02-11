_e_kbd_int_matches_free(E_Kbd_Int *ki)
{
   E_Kbd_Int_Match *km;

   EINA_LIST_FREE(ki->matches, km)
     {
        if (km->str) eina_stringshare_del(km->str);
        evas_object_del(km->obj);
        free(km);
     }
}
