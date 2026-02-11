timevar_realtime_get(int code, vpiHandle ref)
{
      switch (code) {
          case vpiSize:
	    return 1;

          case vpiSigned:
	    return 0;

	  case vpiFuncType:
	    return vpiRealFunc;

          case vpiAutomatic:
	    return 0;

	  default:
	    fprintf(stderr, "Code: %d\n", code);
	    assert(0);
	    return 0;
      }
}
