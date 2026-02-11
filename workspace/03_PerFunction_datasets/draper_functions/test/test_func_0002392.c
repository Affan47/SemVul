netsnmp_access_interface_entry_guess_speed(netsnmp_interface_entry *entry)
{
    if (entry->type == IANAIFTYPE_ETHERNETCSMACD)
        entry->speed = 10000000;
    else if (entry->type == IANAIFTYPE_SOFTWARELOOPBACK)
        entry->speed = 10000000;
    else if (entry->type == IANAIFTYPE_ISO88025TOKENRING)
        entry->speed = 4000000;
    else
        entry->speed = 0;
    entry->speed_high = entry->speed / 1000000LL;
}
