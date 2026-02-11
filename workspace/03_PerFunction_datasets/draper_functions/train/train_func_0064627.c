VQuerytag(int32 vkey )
{
    vginstance_t *v = NULL;
    VGROUP       *vg = NULL;
    int32      ret_value = SUCCEED;
    CONSTR(FUNC, "Vgettagref");


    HEclear();


    if (HAatom_group(vkey)!=VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if (NULL == (v = (vginstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);


    vg = v->vg;
    if (vg == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    ret_value = ((int32) vg->otag);

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
