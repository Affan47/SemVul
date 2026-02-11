clear()
{

    errorFlag = DcmElement::clear();

    fStringMode = DCM_UnknownString;
    return errorFlag;
}
