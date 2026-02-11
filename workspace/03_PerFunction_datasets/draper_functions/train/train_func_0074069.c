update_os_stats(uint8_t detection)
{
    switch (detection) {

        case CO_SYN:
        case CO_SYNACK:
        case CO_ACK:
        case CO_FIN:
        case CO_RST:
            config.pr_s.tcp_os_assets++;
            break;
        case CO_UDP:
            config.pr_s.udp_os_assets++;
            break;
        case CO_ICMP:
            config.pr_s.icmp_os_assets++;
            break;
        case CO_DHCP:
            config.pr_s.dhcp_os_assets++;
            break;
        default:
            break;
    }
}
