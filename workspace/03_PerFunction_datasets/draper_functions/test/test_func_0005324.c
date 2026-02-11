e_gadcon_client_config_del(E_Config_Gadcon *cf_gc, E_Config_Gadcon_Client *cf_gcc)
{
   E_Gadcon *gc;
   Eina_List *l, *ll;

   if (!cf_gcc) return;
   EINA_LIST_FOREACH(gadcons, l, gc)
     {
        if (!gc->awaiting_classes) continue;
        ll = eina_hash_find(gc->awaiting_classes, cf_gcc->name);
        eina_hash_set(gc->awaiting_classes, cf_gcc->name, eina_list_remove(ll, cf_gcc));
     }

   eina_stringshare_del(cf_gcc->name);
   eina_stringshare_del(cf_gcc->id);
   eina_stringshare_del(cf_gcc->style);
   if (cf_gc) cf_gc->clients = eina_list_remove(cf_gc->clients, cf_gcc);
   free(cf_gcc);
}
