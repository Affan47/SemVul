scan_format_float(vpiHandle callh, vpiHandle argv,
                             struct byte_source *src, unsigned width,
                             unsigned suppress_flag, PLI_BYTE8 *name,
                             char code)
{
      vpiHandle arg;
      int match;
      s_vpi_value val;
      double result;


      result = get_float(src, width, &match);


      if (match == 0) return 0;


      if (suppress_flag) return -1;


      arg = vpi_scan(argv);
      if (! arg) {
	    vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("%s() ran out of variables for %%%c format code.",
	               name, code);
	    vpi_control(vpiFinish, 1);
	    return 0;
      }


      val.format = vpiRealVal;
      val.value.real = result;
      vpi_put_value(arg, &val, 0, vpiNoDelay);


      return 1;
}
