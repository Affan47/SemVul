AI_xdr_int(XDR *xdr, void *ip)
{
  FUNCNAME("AI_xdr_int");

  TEST_EXIT(sizeof(int) == 4,
	    "sizeof(int) != 4, please start hacking!");
#if HAVE_XDR_INT32_T
  return (xdr_int32_t(xdr,(int *)ip));
#elif HAVE_XDR_INT
  return (xdr_int(xdr,(int *)ip));
#endif
}
