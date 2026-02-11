e_config_binding_signal_match(E_Config_Binding_Signal *eb_in)
{
   Eina_List *l;
   E_Config_Binding_Signal *eb;

   EINA_LIST_FOREACH(e_config->signal_bindings, l, eb)
     {
        if ((eb->context == eb_in->context) &&
            (eb->modifiers == eb_in->modifiers) &&
            (eb->any_mod == eb_in->any_mod) &&
            (((eb->signal) && (eb_in->signal) && (!strcmp(eb->signal, eb_in->signal))) ||
             ((!eb->signal) && (!eb_in->signal))) &&
            (((eb->source) && (eb_in->source) && (!strcmp(eb->source, eb_in->source))) ||
             ((!eb->source) && (!eb_in->source))) &&
            (((eb->action) && (eb_in->action) && (!strcmp(eb->action, eb_in->action))) ||
             ((!eb->action) && (!eb_in->action))) &&
            (((eb->params) && (eb_in->params) && (!strcmp(eb->params, eb_in->params))) ||
             ((!eb->params) && (!eb_in->params))))
          return eb;
     }
   return NULL;
}
