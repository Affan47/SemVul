HPDF_LineAnnot_SetCaption (HPDF_Annotation annot, HPDF_BOOL showCaption, HPDF_LineAnnotCapPosition position, HPDF_INT horzOffset, HPDF_INT vertOffset)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Array capOffset;
    HPDF_PTRACE((" HPDF_LineAnnot_SetCaption\n"));

    ret += HPDF_Dict_AddBoolean ( annot, "Cap", showCaption);
    ret += HPDF_Dict_AddName( annot, "CP", HPDF_LINE_ANNOT_CAP_POSITION_NAMES[(HPDF_INT)position]);

    if (ret != HPDF_OK)
       return HPDF_Error_GetCode ( annot->error);

    capOffset = HPDF_Array_New ( annot->mmgr);
    if ( !capOffset)
        return HPDF_Error_GetCode ( annot->error);

    if ((ret = HPDF_Dict_Add ( annot, "CO", capOffset)) != HPDF_OK)
        return ret;

    ret += HPDF_Array_AddNumber (capOffset, horzOffset);
    ret += HPDF_Array_AddNumber (capOffset, vertOffset);

    if (ret != HPDF_OK)
       return HPDF_Error_GetCode (capOffset->error);

    return HPDF_OK;
}
