sys_end_of_compile(p_cb_data cb_data)
{


      free(timeformat_info.suff);
      timeformat_info.suff  = strdup("");
      timeformat_info.units = vpi_get(vpiTimePrecision, 0);
      timeformat_info.prec  = 0;
      timeformat_info.width = 20;
      return 0;
}
