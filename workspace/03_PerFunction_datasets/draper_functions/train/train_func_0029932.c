_e_shelf_free_cb(void *data __UNUSED__, void *event)
{
   E_Event_Shelf *ev = event;
   E_Shelf *es = ev->shelf;

   eina_stringshare_del(es->name);
   eina_stringshare_del(es->style);

   if (es->cfg_delete)
     {
        if (es->cfg)
          {
             e_config->shelves = eina_list_remove(e_config->shelves, es->cfg);
             eina_stringshare_del(es->cfg->name);
             eina_stringshare_del(es->cfg->style);
             free(es->cfg);
          }
        e_config_save_queue();
     }
   free(es);
   free(ev);
}
