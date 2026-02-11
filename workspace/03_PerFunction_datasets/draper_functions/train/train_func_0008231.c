on_tf_ok_clicked                       (GtkButton       *button,
                                        EasySpice *es)
{
  clean_log(es);
  led_off(es->win_main);
  if (strlen(es->project) == 0) {
    write_log(_("Error: No project name specified\n"));
    write_log(_("Error: project name missing, stopped simulation\n"));
    return;
  }
  if (netlist_test(es, FALSE))
    create_quickmessage(_("Error"),_("error(s) in the netlist\n"
			      "No simulation done\n"));
  else {
    spice_variables_get_entries(es->win_main, es->spice_vars);
    if (spice_test_field(es, SIMUL_TF)) {
      simul(es, SIMUL_TF);
    }
  }
}
