sys_monitor_compiletf(PLI_BYTE8 *name)
{
      vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
      vpiHandle argv = vpi_iterate(vpiArgument, callh);

      if (sys_check_args(callh, argv, name, 1, 1)) vpi_control(vpiFinish, 1);
      return 0;
}
