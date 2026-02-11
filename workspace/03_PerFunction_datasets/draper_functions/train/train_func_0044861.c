juniper_es_print(const struct pcap_pkthdr *h, register const u_char *p)
{
        struct juniper_l2info_t l2info;
        struct juniper_ipsec_header {
            u_int8_t sa_index[2];
            u_int8_t ttl;
            u_int8_t type;
            u_int8_t spi[4];
            u_int8_t src_ip[4];
            u_int8_t dst_ip[4];
        };
        u_int rewrite_len,es_type_bundle;
        const struct juniper_ipsec_header *ih;

        l2info.pictype = DLT_JUNIPER_ES;
        if(juniper_parse_header(p, h, &l2info) == 0)
            return l2info.header_len;

        p+=l2info.header_len;
        ih = (struct juniper_ipsec_header *)p;

        switch (ih->type) {
        case JUNIPER_IPSEC_O_ESP_ENCRYPT_ESP_AUTHEN_TYPE:
        case JUNIPER_IPSEC_O_ESP_ENCRYPT_AH_AUTHEN_TYPE:
            rewrite_len = 0;
            es_type_bundle = 1;
            break;
        case JUNIPER_IPSEC_O_ESP_AUTHENTICATION_TYPE:
        case JUNIPER_IPSEC_O_AH_AUTHENTICATION_TYPE:
        case JUNIPER_IPSEC_O_ESP_ENCRYPTION_TYPE:
            rewrite_len = 16;
            es_type_bundle = 0;
        default:
            printf("ES Invalid type %u, length %u",
                   ih->type,
                   l2info.length);
            return l2info.header_len;
        }

        l2info.length-=rewrite_len;
        p+=rewrite_len;

        if (eflag) {
            if (!es_type_bundle) {
                printf("ES SA, index %u, ttl %u type %s (%u), spi %u, Tunnel %s > %s, length %u\n",
                       EXTRACT_16BITS(&ih->sa_index),
                       ih->ttl,
                       tok2str(juniper_ipsec_type_values,"Unknown",ih->type),
                       ih->type,
                       EXTRACT_32BITS(&ih->spi),
                       ipaddr_string(&ih->src_ip),
                       ipaddr_string(&ih->dst_ip),
                       l2info.length);
            } else {
                printf("ES SA, index %u, ttl %u type %s (%u), length %u\n",
                       EXTRACT_16BITS(&ih->sa_index),
                       ih->ttl,
                       tok2str(juniper_ipsec_type_values,"Unknown",ih->type),
                       ih->type,
                       l2info.length);
            }
        }

        ip_print(gndo, p, l2info.length);
        return l2info.header_len;
}
