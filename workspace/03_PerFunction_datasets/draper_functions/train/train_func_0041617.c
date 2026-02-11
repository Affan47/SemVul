init_ip_scalars(void)
{
    static oid 	    ipForwarding_oid[] = { 1, 3, 6, 1, 2, 1, 4, 1 };
    static oid 	    ipDefaultTTL_oid[] = { 1, 3, 6, 1, 2, 1, 4, 2, 0 };
    static oid      ipReasmTimeout_oid[] = { 1, 3, 6, 1, 2, 1, 4, 13, 0 };
    static oid      ipv6IpForwarding_oid[] = { 1, 3, 6, 1, 2, 1, 4, 25 };
    static oid      ipv6IpDefaultHopLimit_oid[] =
        { 1, 3, 6, 1, 2, 1, 4, 26, 0 };
    static oid      ipAddressSpinLock_oid[] = { 1, 3, 6, 1, 2, 1, 4, 33 };

    DEBUGMSGTL(("ip_scalar", "Initializing\n"));

    netsnmp_register_num_file_instance
        ("ipReasmTimeout",
         ipReasmTimeout_oid, OID_LENGTH(ipReasmTimeout_oid),
         "/proc/sys/net/ipv4/ipfrag_time", ASN_INTEGER,
         HANDLER_CAN_RONLY, NULL, NULL);

    netsnmp_register_scalar(netsnmp_create_handler_registration
                             ("ipForwarding", handle_ipForwarding,
                              ipForwarding_oid,
                              OID_LENGTH(ipForwarding_oid),
                              HANDLER_CAN_RWRITE));

    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("ipv6IpForwarding", handle_ipv6IpForwarding,
                             ipv6IpForwarding_oid,
                             OID_LENGTH(ipv6IpForwarding_oid),
                             HANDLER_CAN_RWRITE));

    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("ipAddressSpinLock", handle_ipAddressSpinLock,
                             ipAddressSpinLock_oid,
                             OID_LENGTH(ipAddressSpinLock_oid),
                             HANDLER_CAN_RWRITE));


    ipAddressSpinLockValue = (int) random();

    netsnmp_register_num_file_instance
        ("ipv6IpDefaultHopLimit",
         ipv6IpDefaultHopLimit_oid, OID_LENGTH(ipv6IpDefaultHopLimit_oid),
         "/proc/sys/net/ipv6/conf/default/hop_limit", ASN_INTEGER,
         HANDLER_CAN_RWRITE, NULL, NULL);

     netsnmp_register_num_file_instance
        ("ipDefaultTTL",
         ipDefaultTTL_oid, OID_LENGTH(ipDefaultTTL_oid),
         "/proc/sys/net/ipv4/ip_default_ttl", ASN_INTEGER,
         HANDLER_CAN_RWRITE, NULL, NULL);

}
