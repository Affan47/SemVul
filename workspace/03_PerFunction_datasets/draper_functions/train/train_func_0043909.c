sys_fseek_compiletf(PLI_BYTE8*name)
{
      vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
      vpiHandle argv = vpi_iterate(vpiArgument, callh);
      vpiHandle arg;


      if (argv == 0) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s requires three arguments.\n", name);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }


      if (! is_numeric_obj(vpi_scan(argv))) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s's first argument must be numeric.\n", name);
	    vpi_control(vpiFinish, 1);
      }


      arg = vpi_scan(argv);
      if (! arg) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s requires a second (numeric) argument.\n", name);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }

      if (! is_numeric_obj(arg)) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s's second argument must be numeric.\n", name);
	    vpi_control(vpiFinish, 1);
      }


      arg = vpi_scan(argv);
      if (! arg) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s requires a third (numeric) argument.\n", name);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }

      if (! is_numeric_obj(arg)) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s's third argument must be numeric.\n", name);
	    vpi_control(vpiFinish, 1);
      }


      check_for_extra_args(argv, callh, name, "three arguments", 0);

      return 0;
}
