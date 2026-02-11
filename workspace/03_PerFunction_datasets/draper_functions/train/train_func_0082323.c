e_bindings_key_get(const char *action)
{
   E_Binding_Key *binding;
   Eina_List *l;

   EINA_LIST_FOREACH(key_bindings, l, binding)
     {
        if (binding->action && action && !strcmp(action, binding->action))
          return binding;
     }
   return NULL;
}
