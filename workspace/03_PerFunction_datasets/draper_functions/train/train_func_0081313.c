get_link_level_hdr_length(int type)
{
    switch (type) {
        case DLT_EN10MB:
            return 14;

        case DLT_SLIP:
            return 16;

        case DLT_SLIP_BSDOS:
            return 24;

        case DLT_NULL:
#ifdef DLT_LOOP
        case DLT_LOOP:
#endif
            return 4;

        case DLT_PPP:
#ifdef DLT_C_HDLC
        case DLT_C_HDLC:
#endif
#ifdef DLT_PPP_SERIAL
        case DLT_PPP_SERIAL:
#endif
            return 4;

        case DLT_PPP_BSDOS:
            return 24;

        case DLT_FDDI:
            return 21;

        case DLT_IEEE802:
            return 22;

#ifdef DLT_ATM_RFC1483
        case DLT_ATM_RFC1483:
            return 8;
#endif

#ifdef DLT_PRISM_HEADER
        case DLT_PRISM_HEADER:
            return 32;
#endif

        case DLT_RAW:
            return 0;

#ifdef DLT_ATM_CLIP
        case DLT_ATM_CLIP:
            return 8;
#endif

#ifdef DLT_LINUX_SLL
        case DLT_LINUX_SLL:
            return 16;
#endif

#ifdef DLT_IEEE802_11
        case DLT_IEEE802_11:
            return 32;
#endif

        default:;
    }
    fprintf(stderr, PROGNAME": unknown data link type %d", type);
    exit(1);
}
