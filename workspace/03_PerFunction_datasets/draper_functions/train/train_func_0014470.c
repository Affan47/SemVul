glue_vhdl_proc_call(void *_cpssp, const char *proc)
{
	struct glue_vhdl *cpssp = (struct glue_vhdl *)_cpssp;
	if (strcmp(proc, "send_string") == 0) {
		union fauhdli_value dest_driver;
		union fauhdli_value s_array;
		union fauhdli_value s_lb;
		union fauhdli_value s_ub;

		glue_vhdl_get_arg(cpssp, "dest__driver__", &dest_driver);
		glue_vhdl_get_arg(cpssp, "s", &s_array);
		glue_vhdl_get_arg(cpssp, "s_lb_0", &s_lb);
		glue_vhdl_get_arg(cpssp, "s_rb_0", &s_ub);

		glue_vhdl_send_string(dest_driver, s_array, s_lb, s_ub);

	} else if (strcmp(proc, "terminate") == 0) {
		glue_vhdl_terminate();

	} else if (strcmp(proc, "debug") == 0) {
		glue_vhdl_toggle_debug();

	} else if ((strcmp(proc, "shortcut_bool_out") == 0)
		|| (strcmp(proc, "shortcut_int_out")  == 0)) {
		union fauhdli_value s_driver;
		union fauhdli_value comp_array;
		union fauhdli_value comp_lb;
		union fauhdli_value comp_ub;
		union fauhdli_value comp_port_array;
		union fauhdli_value comp_port_lb;
		union fauhdli_value comp_port_ub;

		glue_vhdl_get_arg(cpssp, "s__driver__", &s_driver);
		glue_vhdl_get_arg(cpssp, "comp", &comp_array);
		glue_vhdl_get_arg(cpssp, "comp_lb_0", &comp_lb);
		glue_vhdl_get_arg(cpssp, "comp_rb_0", &comp_ub);
		glue_vhdl_get_arg(cpssp, "comp_port", &comp_port_array);
		glue_vhdl_get_arg(cpssp, "comp_port_lb_0", &comp_port_lb);
		glue_vhdl_get_arg(cpssp, "comp_port_rb_0", &comp_port_ub);

		glue_vhdl_shorcut_drv_out(
				s_driver,
				comp_array,
				comp_lb,
				comp_ub,
				comp_port_array,
				comp_port_lb,
				comp_port_ub);
	} else {

		faum_log(FAUM_LOG_FATAL, "glue-vhdl", __func__,
			"Trying to call unimplemented foreign procedure "
			"%s.\n", proc);
		assert(0);
	}

	cpssp->num_params = 0;
}
