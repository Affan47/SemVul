e_config_binding_mouse_match(E_Config_Binding_Mouse *eb_in)
{
   Eina_List *l;
   E_Config_Binding_Mouse *eb;

   EINA_LIST_FOREACH(e_config->mouse_bindings, l, eb)
     {
        if ((eb->context == eb_in->context) &&
            (eb->button == eb_in->button) &&
            (eb->modifiers == eb_in->modifiers) &&
            (eb->any_mod == eb_in->any_mod) &&
            (((eb->action) && (eb_in->action) && (!strcmp(eb->action, eb_in->action))) ||
             ((!eb->action) && (!eb_in->action))) &&
            (((eb->params) && (eb_in->params) && (!strcmp(eb->params, eb_in->params))) ||
             ((!eb->params) && (!eb_in->params))))
          return eb;
     }
   return NULL;
}
