e_action_predef_name_set(const char *act_grp, const char *act_name, const char *act_cmd, const char *act_params, const char *param_example, int editable)
{
   E_Action_Group *actg = NULL;
   E_Action_Description *actd = NULL;
   Eina_List *l;

   if ((!act_grp) || (!act_name)) return;

   EINA_LIST_FOREACH(action_groups, l, actg)
     {
        if (!strcmp(actg->act_grp, act_grp)) break;
        actg = NULL;
     }

   if (!actg)
     {
        actg = E_NEW(E_Action_Group, 1);
        if (!actg) return;

        actg->act_grp = eina_stringshare_add(act_grp);
        actg->acts = NULL;

        action_groups = eina_list_append(action_groups, actg);
        action_groups =
          eina_list_sort(action_groups, -1, _action_groups_sort_cb);
     }

   EINA_LIST_FOREACH(actg->acts, l, actd)
     {
        if (!strcmp(actd->act_name, act_name)) break;
        actd = NULL;
     }

   if (actd) return;

   actd = E_NEW(E_Action_Description, 1);
   if (!actd) return;

   actd->act_name = eina_stringshare_add(act_name);
   actd->act_cmd = !act_cmd ? NULL : eina_stringshare_add(act_cmd);
   actd->act_params = !act_params ? NULL : eina_stringshare_add(act_params);
   actd->param_example = !param_example ? NULL : eina_stringshare_add(param_example);
   actd->editable = editable;

   actg->acts = eina_list_append(actg->acts, actd);
}
