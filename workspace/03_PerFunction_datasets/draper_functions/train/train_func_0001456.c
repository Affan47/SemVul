run(
  const gchar *     name,
  gint              nparams,
	const GimpParam * param,
	gint *            nreturn_vals,
	GimpParam **      return_vals)
{
  static GimpParam values[1];
  TGimpAdapterParameters parameters;
  gboolean ok;


  *nreturn_vals = 1;
  *return_vals = values;
  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = GIMP_PDB_SUCCESS;


#if defined(G_OS_WIN32)
  bindtextdomain (GETTEXT_PACKAGE, gimp_locale_directory());
#else
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
#endif
#ifdef HAVE_BIND_TEXTDOMAIN_CODESET
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif
  textdomain (GETTEXT_PACKAGE);


  gint32 drawable_id;
  drawable_id = param[2].data.d_drawable;


  ok = FALSE;
  switch(param[0].data.d_int32)
  {
    case GIMP_RUN_INTERACTIVE :
      get_last_parameters(&parameters, drawable_id, RESYNTH_CONTROLS_PDB_NAME );
      init_gtk();

      ok = get_parameters_by_asking(&parameters,drawable_id);
      if (ok)
        set_last_parameters(&parameters, drawable_id);
      break;
    case GIMP_RUN_NONINTERACTIVE :

      ok = get_parameters_from_list(&parameters, nparams, param);
      break;
    case GIMP_RUN_WITH_LAST_VALS :
      ok = get_last_parameters(&parameters,drawable_id, RESYNTH_CONTROLS_PDB_NAME);
      break;
  }

  if (!ok)
  {


    values[0].data.d_status = GIMP_PDB_EXECUTION_ERROR;
    return;
  }


  static GimpParam temp[RESYNTH_PARAMETER_COUNT];
  set_parameters_to_list(&parameters, param, nparams, GIMP_RUN_NONINTERACTIVE, temp);


  GimpParam * engine_result;
  gint engine_n_return_vals;
  engine_result = gimp_run_procedure2(
    RESYNTH_ENGINE_PDB_NAME,
    &engine_n_return_vals,
    RESYNTH_PARAMETER_COUNT,
    temp
    );


  if (engine_result[0].data.d_status != GIMP_PDB_SUCCESS)
  {

    *nreturn_vals = engine_n_return_vals;
    *return_vals = engine_result;
  }
  else
  {

    gimp_destroy_params(engine_result, engine_n_return_vals);
  }
}
