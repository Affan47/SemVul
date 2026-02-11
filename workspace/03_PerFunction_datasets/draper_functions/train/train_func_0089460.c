tf_irosynchronize(void*obj)
{
      vpiHandle sys = (vpiHandle)obj;
      p_pli_data pli = vpi_get_userdata(sys);
      s_cb_data cb;
      s_vpi_time ti = {vpiSuppressTime, 0, 0};

      cb.reason = cbReadOnlySynch;
      cb.cb_rtn = callback;
      cb.obj = sys;
      cb.time = &ti;
      cb.user_data = (char *)pli;

      vpi_register_cb(&cb);

      if (pli_trace)
	    fprintf(pli_trace, "tf_irosynchronize(%p) --> %d\n", obj, 0);

      return 0;
}
