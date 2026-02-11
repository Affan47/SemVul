spice_view_result(EasySpice *es, int type_simul, int n_step)
{
  char *buf;

  switch(type_simul) {
  case SIMUL_OP:


    if (es->spice_vars->op_show_results_schematic != FALSE) {
      visu_result_gschem(es);
      buf=g_strdup_printf("gschem %s &",es->file_schematic_tmp);
      if (VERBOSE1)
	printf("executing: \"%s\"\n",buf);
      system(buf);
      g_free(buf);
    }
    break;
  case SIMUL_DC:
    create_spice_plot_file(es, n_step, type_simul);
    if (es->spice_vars->plot_autoupdate != FALSE)
      start_plot(es);
    break;
  case SIMUL_AC:
    create_spice_plot_file(es, n_step, type_simul);
    if (es->spice_vars->plot_autoupdate != FALSE)
      start_plot(es);
    break;
  case SIMUL_NOISE:
    create_spice_plot_file(es, n_step, type_simul);
    if (es->spice_vars->plot_autoupdate != FALSE)
      start_plot(es);
    break;
  case SIMUL_TRAN:
    create_spice_plot_file(es, n_step,type_simul);
    if (es->spice_vars->plot_autoupdate != FALSE)
      start_plot(es);
    break;
  case SIMUL_TF:
    break;
  }
}
