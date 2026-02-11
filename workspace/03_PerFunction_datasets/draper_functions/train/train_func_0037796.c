se_find_list(unsigned int major, unsigned int minor)
{
    if (major > current_maj_num || minor > current_min_num)
        return NULL;
    netsnmp_assert(NULL != snmp_enum_lists);

    return snmp_enum_lists[major][minor];
}
