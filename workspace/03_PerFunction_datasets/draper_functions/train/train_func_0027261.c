elm_genlist_item_decorate_mode_set(Elm_Object_Item *item,
                                   const char *decorate_it_type,
                                   Eina_Bool decorate_it_set)
{
   Elm_Gen_Item *it = (Elm_Gen_Item *)item;
   Elm_Genlist_Smart_Data *sd;
   Elm_Object_Item *it2;
   Eina_List *l;

   ELM_GENLIST_ITEM_CHECK_OR_RETURN(item);
   sd = GL_IT(it)->wsd;

   if (!decorate_it_type) return;
   if ((it->generation < sd->generation) ||
       elm_widget_item_disabled_get(it)) return;
   if (sd->decorate_all_mode) return;

   if ((sd->mode_item == it) &&
       (!strcmp(decorate_it_type, sd->decorate_it_type)) &&
       (decorate_it_set))
     return;
   if (!it->itc->decorate_item_style) return;
   it->decorate_it_set = decorate_it_set;

   if (sd->multi)
     {
        EINA_LIST_FOREACH (sd->selected, l, it2)
          if (((Elm_Gen_Item *)it2)->realized)
            elm_genlist_item_selected_set(it2, EINA_FALSE);
     }
   else
     {
        it2 = elm_genlist_selected_item_get(ELM_WIDGET_DATA(sd)->obj);
        if ((it2) && (((Elm_Gen_Item *)it2)->realized))
          elm_genlist_item_selected_set(it2, EINA_FALSE);
     }

   if (((sd->decorate_it_type)
        && (strcmp(decorate_it_type, sd->decorate_it_type))) ||
       (decorate_it_set) || ((it == sd->mode_item) && (!decorate_it_set)))
     _decorate_item_unset(sd);

   eina_stringshare_replace(&sd->decorate_it_type, decorate_it_type);
   if (decorate_it_set) _decorate_item_set(it);
}
