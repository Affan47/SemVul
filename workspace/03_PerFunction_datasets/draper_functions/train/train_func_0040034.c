is_valid_header(COW_Header & header)
{
    if(header.id[0] != 'C' || header.id[1] != 'O' || header.id[2] != 'W' ||
            header.id[3] != 'D')
    {
        BX_DEBUG(("not a vmware3 COW disk"));
        return false;
    }

    if(header.header_version != 3)
    {
        BX_DEBUG(("unsupported vmware3 COW disk header version"));

        return false;
    }

    if(header.vmware_version != 2)
    {
        BX_DEBUG(("unsupported vmware3 COW disk version"));
        return false;
    }

    return true;
}
