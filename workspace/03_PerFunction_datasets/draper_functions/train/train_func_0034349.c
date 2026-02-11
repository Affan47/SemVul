elm_scroller_policy_set(Evas_Object *obj,
                        Elm_Scroller_Policy policy_h,
                        Elm_Scroller_Policy policy_v)
{
   ELM_SCROLLABLE_CHECK(obj);

   if ((policy_h >= ELM_SCROLLER_POLICY_LAST) ||
       (policy_v >= ELM_SCROLLER_POLICY_LAST))
     return;

   s_iface->policy_set(obj, policy_h, policy_v);
}
