external_multibuttonentry_params_parse(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const Eina_List *params)
{
   Elm_Params_Multibuttonentry *mem = NULL;
   Edje_External_Param *param;
   const Eina_List *l;


   if (!mem)
     return NULL;

   EINA_LIST_FOREACH(params, l, param)
     {
        if (!strcmp(param->name, "label"))
          mem->label = eina_stringshare_add(param->s);
        else if (!strcmp(param->name, "guide text"))
          mem->guide_text = eina_stringshare_add(param->s);
     }

   return mem;
}
