sys_fflush_calltf(PLI_BYTE8*name)
{
      vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
      vpiHandle argv = vpi_iterate(vpiArgument, callh);
      vpiHandle arg;
      s_vpi_value val;
      PLI_UINT32 fd_mcd;
      FILE *fp;
      errno = 0;


      if (argv == 0) {
	    fflush(NULL);
	    return 0;
      }


      arg = vpi_scan(argv);
      vpi_free_object(argv);
      val.format = vpiIntVal;
      vpi_get_value(arg, &val);
      fd_mcd = val.value.integer;


      if (fd_mcd == 0) return 0;

      if ((! IS_MCD(fd_mcd) && vpi_get_file(fd_mcd) == NULL) ||
          ( IS_MCD(fd_mcd) && vpi_mcd_printf(fd_mcd, "%s", "") == EOF) ||
          (! fd_mcd)) {
	    vpi_printf("WARNING: %s:%d: ", vpi_get_str(vpiFile, callh),
	               (int)vpi_get(vpiLineNo, callh));
	    vpi_printf("invalid file descriptor/MCD (0x%x) given to %s.\n",
	               (unsigned int)fd_mcd, name);
	    errno = EBADF;
	    return 0;
      }

      if (IS_MCD(fd_mcd)) {
	    vpi_mcd_flush(fd_mcd);
      } else {

	    fp = vpi_get_file(fd_mcd);
	    if (fp) fflush(fp);
      }

      return 0;
}
