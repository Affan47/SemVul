vpip_scope(__vpiRealVar*sig)
{
      if (sig->is_netarray)
	    return  (struct __vpiScope*) vpi_handle(vpiScope, sig->within.parent);
      else
	    return sig->within.scope;
}
