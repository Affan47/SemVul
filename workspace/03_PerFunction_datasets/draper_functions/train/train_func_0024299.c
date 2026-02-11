_e_toolbar_fm2_changed(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   E_Toolbar *tbar;
   Eina_List *l = NULL;
   E_Gadcon_Client *gcc = NULL;

   tbar = data;
   if (!tbar) return;
   EINA_LIST_FOREACH(tbar->gadcon->clients, l, gcc)
     {
        if (!gcc) continue;
        evas_object_smart_callback_call(gcc->o_base, "changed", tbar);
     }
}
