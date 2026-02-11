_engines_list_fill(Evas_Object *l_widget,
                   Eina_List   *e_names)
{
   const char *engine, *cur_engine;
   void *sel_it = NULL;
   Eina_List *l;

   if (!e_names)
     return;

   cur_engine = elm_config_engine_get();

   EINA_LIST_FOREACH(e_names, l, engine)
     {
        const char *label;
        Elm_Object_Item *list_it;

        if (!_elm_engine_supported(engine))
          continue;

        label = _engine_name_prettify(engine);

        list_it = elm_list_item_append(l_widget, label, NULL, NULL, NULL,
                                  strdup(engine));
        elm_object_item_del_cb_set(list_it, _engines_list_item_del_cb);
        free((void *)label);

        if (!strcmp(cur_engine, engine))
          sel_it = list_it;
     }

   if (sel_it) elm_list_item_selected_set(sel_it, EINA_TRUE);
   elm_list_go(l_widget);
}
