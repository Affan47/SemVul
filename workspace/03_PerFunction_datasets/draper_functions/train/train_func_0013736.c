acc_fetch_type(handle obj)
{
      switch (vpi_get(vpiType, obj)) {

	  case vpiConstant:


	    if (vpi_get(vpiConstType, obj) == vpiStringConst)
		  return accParameter;
	    else
		  return accConstant;

	  case vpiNamedEvent:
	    return accNamedEvent;

	  case vpiNet:
	    return accNet;

	  case vpiParameter:
	    return accParameter;

	  case vpiReg:
	    return accReg;

	  case vpiIntegerVar:
	    return accIntegerVar;

	  case vpiModule:
	    return accModule;
      }

      vpi_printf("acc_fetch_type: vpiType %d is what accType?\n",
                 (int)vpi_get(vpiType, obj));
      return accUnknown;
}
