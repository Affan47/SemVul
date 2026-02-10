VSsetexternalfile(int32 vkey, const char *filename, int32 offset)
{
    CONSTR(FUNC, "VSsetexternalfile");
    int32       ret_value = SUCCEED;

    vsinstance_t *w;
    VDATA      *vs;
    intn       status;

    if(!filename || offset < 0)
	HGOTO_ERROR(DFE_ARGS, FAIL);

    if (HAatom_group(vkey)!=VSIDGROUP)
	    HGOTO_ERROR(DFE_ARGS, FAIL);


    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    vs = w->vs;
    if (vs->access != 'w')
        HGOTO_ERROR(DFE_BADACC, FAIL);

    if (FAIL == vexistvs(vs->f, vs->oref))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    if(!w->ref)
        HGOTO_ERROR(DFE_NOVS, FAIL);


    status = (intn)HXcreate(vs->f, (uint16)VSDATATAG, (uint16) w->ref,
		      filename, offset, (int32)0);
    if(status != FAIL)
      {
        if((vs->aid != 0) && (vs->aid != FAIL))
            Hendaccess(vs->aid);
        vs->aid = status;
      }
    else
        ret_value = FAIL;

done:
    if(ret_value == FAIL)
    {

    }


    return ret_value;
}
