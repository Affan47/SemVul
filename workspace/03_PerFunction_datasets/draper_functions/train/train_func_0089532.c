m_CopyContainer(Object *in, Object *out)
{
    enum _dxd_copy how = COPY_ATTRIBUTES;

    if (!in[0]) {
        DXSetError(ERROR_BAD_PARAMETER, "#10000", "input");
        return ERROR;
    }

    out[0] = DXCopy(in[0], how);
    return (out[0] != NULL ? OK : ERROR);
}
