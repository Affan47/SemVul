_item_tree_effect(Elm_Genlist_Smart_Data *sd,
                  int y)
{
   Elm_Gen_Item *it = NULL, *expanded_next_it;

   expanded_next_it = sd->expanded_next_item;

   if (sd->move_effect_mode == ELM_GENLIST_TREE_EFFECT_EXPAND)
     {
        it = (Elm_Gen_Item *)elm_genlist_item_prev_get
            ((Elm_Object_Item *)expanded_next_it);
        while (it)
          {
             if (it->item->expanded_depth <=
                 expanded_next_it->item->expanded_depth) break;
             if (it->item->scrl_y &&
                 (it->item->scrl_y <= expanded_next_it->item->old_scrl_y + y)
                 && (it->item->expanded_depth >
                     expanded_next_it->item->expanded_depth))
               {
                  if (!it->item->tree_effect_finished)
                    {
                       edje_object_signal_emit(VIEW(it), "flip_item", "");
                       _item_position
                         (it, VIEW(it), it->item->scrl_x, it->item->scrl_y);
                       it->item->tree_effect_finished = EINA_TRUE;
                    }
               }
             it = (Elm_Gen_Item *)elm_genlist_item_prev_get
                 ((Elm_Object_Item *)it);
          }
     }
   else if (sd->move_effect_mode == ELM_GENLIST_TREE_EFFECT_CONTRACT)
     {
        it = (Elm_Gen_Item *)elm_genlist_item_prev_get
            ((Elm_Object_Item *)expanded_next_it);
        while (it)
          {
             if ((it->item->scrl_y > expanded_next_it->item->old_scrl_y + y) &&
                 (it->item->expanded_depth >
                  expanded_next_it->item->expanded_depth))
               {
                  if (!it->item->tree_effect_finished)
                    {
                       edje_object_signal_emit(VIEW(it), "elm,state,hide", "");
                       it->item->tree_effect_finished = EINA_TRUE;
                    }
               }
             else
               break;
             it = (Elm_Gen_Item *)elm_genlist_item_prev_get
                 ((Elm_Object_Item *)it);
          }
     }
}
