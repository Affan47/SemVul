timevar_realtime_get_str(int code, vpiHandle ref)
{
      switch (code) {
	  case vpiName:
	    return simple_set_rbuf_str("$realtime");
	  default:
	    fprintf(stderr, "Code: %d\n", code);
	    assert(0);
	    return 0;
      }
}
