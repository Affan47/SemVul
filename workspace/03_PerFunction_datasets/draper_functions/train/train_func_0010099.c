e_config_xkb_layout_dup(const E_Config_XKB_Layout *cl)
{
   E_Config_XKB_Layout *cl2;

   EINA_SAFETY_ON_NULL_RETURN_VAL(cl, NULL);
   cl2 = E_NEW(E_Config_XKB_Layout, 1);
   cl2->name = eina_stringshare_ref(cl->name);
   cl2->model = eina_stringshare_ref(cl->model);
   cl2->variant = eina_stringshare_ref(cl->variant);
   return cl2;
}
