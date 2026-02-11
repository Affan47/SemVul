_evas_object_box_insert_at_default(Evas_Object *o, Evas_Object_Box_Data *priv, Evas_Object *child, unsigned int pos)
{
   Eina_List *l;
   unsigned int i;

   if ((pos == 0) && (eina_list_count(priv->children) == 0))
     {
        Evas_Object_Box_Option *new_opt;

        new_opt = _evas_object_box_option_new(o, priv, child);
        if (!new_opt)
          return NULL;

        priv->children = eina_list_prepend(priv->children, new_opt);
        priv->children_changed = EINA_TRUE;
        evas_object_smart_callback_call(o, SIG_CHILD_ADDED, new_opt);
        return new_opt;
     }

   for (l = priv->children, i = 0; l; l = l->next, i++)
     {
        Evas_Object_Box_Option *opt = l->data;

        if (i == pos)
          {
             Evas_Object_Box_Option *new_opt;

             new_opt = _evas_object_box_option_new(o, priv, child);
             if (!new_opt)
               return NULL;

             priv->children = eina_list_prepend_relative
                (priv->children, new_opt, opt);
             priv->children_changed = EINA_TRUE;
             evas_object_smart_callback_call(o, SIG_CHILD_ADDED, new_opt);
             return new_opt;
          }
     }

   return NULL;
}
