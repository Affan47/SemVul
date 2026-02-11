e_action_add(const char *name)
{
   E_Action *act;

   act = e_action_find(name);
   if (!act)
     {
        act = E_OBJECT_ALLOC(E_Action, E_ACTION_TYPE, _e_action_free);
        if (!act) return NULL;
        act->name = name;
        eina_hash_direct_add(actions, act->name, act);
        action_names = eina_list_append(action_names, name);
        action_list = eina_list_append(action_list, act);
     }
   return act;
}
