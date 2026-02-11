evry_action_new(const char *name, const char *label,
                Evry_Type type_in1, Evry_Type type_in2,
                const char *icon,
                int (*action)(Evry_Action *act),
                int (*check_item)(Evry_Action *act, const Evry_Item *it))
{
   Evry_Action *act = EVRY_ITEM_NEW(Evry_Action, _plug, label,
                                    NULL, _action_free_cb);
   if (icon)
     act->base.icon = eina_stringshare_add(icon);

   act->name = eina_stringshare_add(name);

   act->it1.type = type_in1;
   act->it2.type = type_in2;

   act->action = action;
   act->check_item = check_item;

   return act;
}
