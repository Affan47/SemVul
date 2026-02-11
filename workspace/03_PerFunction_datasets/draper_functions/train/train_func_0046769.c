HPDF_Info_SetInfoAttr (HPDF_Dict        info,
                       HPDF_InfoType    type,
                       const char  *value,
                       HPDF_Encoder     encoder)
{
    const char* name = InfoTypeToName (type);

    HPDF_PTRACE((" HPDF_Info_SetInfoAttr\n"));

    if (type <= HPDF_INFO_MOD_DATE)
        return HPDF_SetError (info->error, HPDF_INVALID_PARAMETER, 0);

    if (type == HPDF_INFO_TRAPPED)
        return HPDF_Dict_AddName(info, name, value);

    return HPDF_Dict_Add (info, name, HPDF_String_New (info->mmgr, value,
            encoder));
}
