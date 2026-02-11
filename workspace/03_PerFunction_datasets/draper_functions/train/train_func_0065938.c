_action_free_cb(Evry_Item *it)
{
   GET_ACTION(act, it);

   IF_RELEASE(act->name);

   E_FREE(act);
}
