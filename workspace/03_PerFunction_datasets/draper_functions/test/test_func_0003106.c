parse_icmp (packetinfo *pi)
{
    update_asset(pi);

    if (IS_COSET(&config,CO_ICMP)) {
        if (pi->cxt->check == 0x00) {
            pi->cxt->check = 0x10;
            if (pi->af==AF_INET) {
                fp_icmp4(pi, pi->ip4, pi->icmph, pi->end_ptr);


            } else if (pi->af==AF_INET6) {
                add_asset(pi);
                fp_icmp6(pi, pi->ip6, pi->icmp6h, pi->end_ptr);
            }
        } else {
            vlog(0x3, "[*] - NOT CHECKING ICMP PACKAGE\n");
        }
    }
}
