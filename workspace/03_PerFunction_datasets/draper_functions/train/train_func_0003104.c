_e_gadcon_free(E_Gadcon *gc)
{
   if (gc->dummy)
     dummies = eina_list_remove(dummies, gc);
   else
     {
        e_gadcon_unpopulate(gc);
        gadcons = eina_list_remove(gadcons, gc);
     }
   eina_list_free(gc->populated_classes);
   if (gc->o_container) evas_object_del(gc->o_container);
   eina_stringshare_del(gc->name);
   eina_stringshare_del(gc->edje.swallow_name);
   if (gc->config_dialog) e_object_del(E_OBJECT(gc->config_dialog));
   if (gc->drop_handler) e_drop_handler_del(gc->drop_handler);
   if (gc->cfg_delete)
     {
        eina_stringshare_del(gc->cf->name);
        e_config->gadcons = eina_list_remove(e_config->gadcons, gc->cf);
        free(gc->cf);
        e_config_save_queue();
     }
   free(gc);
}
