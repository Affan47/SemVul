device_already_in_list (SnapScan_Device *current,
                                         SANE_String_Const name)
{
    for (  ;  NULL != current;  current = current->pnext)
    {
        if (0 == strcmp (name, current->dev.name))
            return SANE_TRUE;
    }
    return SANE_FALSE;
}
