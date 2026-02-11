external_genlist_params_parse(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const Eina_List *params)
{
   Elm_Params_Genlist *mem;
   Edje_External_Param *param;
   const Eina_List *l;

   mem = ELM_NEW(Elm_Params_Genlist);
   if (!mem)
     return NULL;

   EINA_LIST_FOREACH(params, l, param)
     {
	if (!strcmp(param->name, "horizontal mode"))
	     mem->horizontal = eina_stringshare_add(param->s);
	else if (!strcmp(param->name, "multi select"))
	  {
	     mem->multi = !!param->i;
	     mem->multi_exists = EINA_TRUE;
	  }
	else if (!strcmp(param->name, "always select"))
	  {
	     mem->always_select = !!param->i;
	     mem->always_select_exists = EINA_TRUE;
	  }
	else if (!strcmp(param->name, "no select"))
	  {
	     mem->no_select = !!param->i;
	     mem->no_select_exists = EINA_TRUE;
	  }
	else if (!strcmp(param->name, "homogeneous"))
	  {
	     mem->homogeneous = !!param->i;
	     mem->homogeneous_exists = EINA_TRUE;
	  }
	else if (!strcmp(param->name, "height bounce"))
	  {
	     mem->h_bounce = !!param->i;
	     mem->h_bounce_exists = EINA_TRUE;
	  }
	else if (!strcmp(param->name, "width bounce"))
	  {
	     mem->v_bounce = !!param->i;
	     mem->v_bounce_exists = EINA_TRUE;
	  }
     }

   return mem;
}
