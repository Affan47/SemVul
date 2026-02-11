external_list_state_set(void *data __UNUSED__, Evas_Object *obj, const void *from_params, const void *to_params, float pos __UNUSED__)
{
   const Elm_Params_List *p;
   Elm_Scroller_Policy policy_h, policy_v;

   if (to_params) p = to_params;
   else if (from_params) p = from_params;
   else return;

   if (p->mode)
     {
        Elm_List_Mode set = _list_mode_setting_get(p->mode);

        if (set != ELM_LIST_LAST)
          elm_list_mode_set(obj, set);
     }

   if ((p->policy_h) && (p->policy_v))
     {
        policy_h = _scroller_policy_choices_setting_get(p->policy_h);
        policy_v = _scroller_policy_choices_setting_get(p->policy_v);
        elm_scroller_policy_set(obj, policy_h, policy_v);
     }
   else if ((p->policy_h) || (p->policy_v))
     {
        elm_scroller_policy_get(obj, &policy_h, &policy_v);
        if (p->policy_h)
          {
             policy_h = _scroller_policy_choices_setting_get(p->policy_h);
             elm_scroller_policy_set(obj, policy_h, policy_v);
          }
        else
          {
             policy_v = _scroller_policy_choices_setting_get(p->policy_v);
             elm_scroller_policy_set(obj, policy_h, policy_v);
          }
     }

   if (p->h_mode_exists)
     elm_list_horizontal_set(obj, p->h_mode);
   if (p->multi_exists)
     elm_list_multi_select_set(obj, p->multi);
   if (p->always_select_exists)
     {
        if (p->always_select)
          elm_list_select_mode_set (obj, ELM_OBJECT_SELECT_MODE_ALWAYS);
        else
          elm_list_select_mode_set (obj, ELM_OBJECT_SELECT_MODE_DEFAULT);
     }
}
