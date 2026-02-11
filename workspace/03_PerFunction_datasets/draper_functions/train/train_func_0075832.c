VSappendable(int32 vkey,
             int32 blk   )
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32      ret_value = SUCCEED;
    CONSTR(FUNC, "VSappendable");


    HEclear();


    blk = blk;


    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);


    vs = w->vs;
    if ((vs == NULL) || (vs->otag != VSDESCTAG))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    if(vs->aid == 0)
        vs->aid = Hstartaccess(vs->f, VSDATATAG, vs->oref, DFACC_RDWR|DFACC_APPENDABLE);
    else
        ret_value = Happendable(vs->aid);

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
