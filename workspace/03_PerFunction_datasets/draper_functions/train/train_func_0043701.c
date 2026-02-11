hsc_base_include_string(HSCPRC * hp, STRPTR filename, STRPTR s, ULONG optn, INFILEPOS * base_pos)
{
    BOOL ok;
    INFILE *inpf = NULL;

    if (optn & IH_POS_PARENT) {
        filename = PARENT_FILE_ID;
        optn &= ~IH_POS_PARENT;
    }
    inpf = infopen_str(filename, s, 0);

    ok = hsc_include(hp, inpf, optn, base_pos);

    return (ok);
}
