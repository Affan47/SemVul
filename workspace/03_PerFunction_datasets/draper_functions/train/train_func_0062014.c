ipAddressAddrType_map(long * mib_ipAddressAddrType_val_ptr,
                      long raw_ipAddressAddrType_val)
{
    netsnmp_assert(NULL != mib_ipAddressAddrType_val_ptr);

    DEBUGMSGTL(("verbose:ipAddressTable:ipAddressAddrType_map",
                "called\n"));


    switch (raw_ipAddressAddrType_val) {
    case INTERNAL_IPADDRESSTABLE_IPADDRESSADDRTYPE_IPV4:
        *mib_ipAddressAddrType_val_ptr = INETADDRESSTYPE_IPV4;
        break;

    case INTERNAL_IPADDRESSTABLE_IPADDRESSADDRTYPE_IPV6:
        *mib_ipAddressAddrType_val_ptr = INETADDRESSTYPE_IPV6;
        break;

    default:
        snmp_log(LOG_ERR, "couldn't map value %ld for ipAddressAddrType\n",
                 raw_ipAddressAddrType_val);
        *mib_ipAddressAddrType_val_ptr = INETADDRESSTYPE_UNKNOWN;
    }

    return MFD_SUCCESS;
}
