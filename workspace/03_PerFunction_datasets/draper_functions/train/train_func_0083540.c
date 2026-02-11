sinfo_rec_jitter_exec(cpl_plugin *plugin)
{

  cpl_recipe *recipe = (cpl_recipe *) plugin;

    cpl_errorstate initial_errorstate = cpl_errorstate_get();


  if (cpl_plugin_get_type(plugin) == CPL_PLUGIN_TYPE_RECIPE)
      recipe = (cpl_recipe *)plugin ;
  else return -1 ;

    if (!cpl_errorstate_is_equal(initial_errorstate)) {


        cpl_errorstate_dump(initial_errorstate, CPL_FALSE, NULL);
    }
  return sinfo_rec_jitter(recipe->parameters, recipe->frames);

}
