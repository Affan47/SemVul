HPDF_TextMarkupAnnot_SetQuadPoints ( HPDF_Annotation annot, HPDF_Point lb, HPDF_Point rb, HPDF_Point lt, HPDF_Point rt)
{
    HPDF_Array quadPoints;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE((" HPDF_TextMarkupAnnot_SetQuadPoints\n"));

    quadPoints = HPDF_Array_New ( annot->mmgr);
    if ( !quadPoints)
        return HPDF_Error_GetCode ( annot->error);

    if ((ret = HPDF_Dict_Add ( annot, "QuadPoints", quadPoints)) != HPDF_OK)
        return ret;

    ret += HPDF_Array_AddReal (quadPoints, lb.x);
    ret += HPDF_Array_AddReal (quadPoints, lb.y);
    ret += HPDF_Array_AddReal (quadPoints, rb.x);
    ret += HPDF_Array_AddReal (quadPoints, rb.y);
    ret += HPDF_Array_AddReal (quadPoints, lt.x);
    ret += HPDF_Array_AddReal (quadPoints, lt.y);
    ret += HPDF_Array_AddReal (quadPoints, rt.x);
    ret += HPDF_Array_AddReal (quadPoints, rt.y);

    if (ret != HPDF_OK)
       return HPDF_Error_GetCode (quadPoints->error);

    return HPDF_OK;
}
