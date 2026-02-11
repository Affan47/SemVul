acc_fetch_itfarg_int(PLI_INT32 n, handle obj)
{
      vpiHandle iter, hand = 0;
      s_vpi_value value;
      int idx = n;
      int rtn;

      iter = vpi_iterate(vpiArgument, obj);


      while (idx > 0 && (hand = vpi_scan(iter))) idx--;

      if (hand) {
	    value.format=vpiIntVal;
	    vpi_get_value(hand, &value);
	    rtn = value.value.integer;
	    vpi_free_object(iter);
      } else {
	    rtn = 0;
      }

      if (pli_trace) {
	    fprintf(pli_trace, "%s: acc_fetch_itfarg_int(%d, %p) --> %d\n",
		    vpi_get_str(vpiName, obj), (int)n, obj, rtn);
      }

      return rtn;
}
