VSofclass(int32 id,
	    const char *vsclass,
	    uintn start_vd,
            uintn n_vds,
            uint16 *refarray	 )
{
    CONSTR(FUNC, "VSofclass");
    intn      ret_value = 0;


    HEclear();


    if (refarray != NULL && n_vds == 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    ret_value = VSIgetvdatas(id, vsclass, start_vd, n_vds, refarray);

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
