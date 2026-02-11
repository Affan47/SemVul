sys_rand_two_args_compiletf(PLI_BYTE8 *name)
{
      vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
      vpiHandle argv = vpi_iterate(vpiArgument, callh);
      vpiHandle seed, arg2;


      if (argv == 0) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s requires two arguments.\n", name);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }


      seed = vpi_scan(argv);
      arg2 = vpi_scan(argv);
      if (arg2 == 0) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s requires two arguments.\n", name);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }


      if (! is_seed_obj(seed, callh, name)) return 0;


      if (! is_numeric_obj(arg2)) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s second argument must be numeric.\n", name);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }


      check_for_extra_args(argv, callh, name, "two arguments", 0);

      return 0;
}
