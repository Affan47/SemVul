tcpTable_load(netsnmp_cache *cache, void *vmagic)
{
    FILE           *in;
    char            line[256];

    tcpTable_free(cache, NULL);

#if HAVE_NETLINK_NETLINK_H
	if (tcpTable_load_netlink() == 0) {
		return 0;
	}
#endif

    if (!(in = fopen("/proc/net/tcp", "r"))) {
        DEBUGMSGTL(("mibII/tcpTable", "Failed to load TCP Table (linux1)\n"));
        NETSNMP_LOGONCE((LOG_ERR, "snmpd: cannot open /proc/net/tcp ...\n"));
        return -1;
    }


    while (line == fgets(line, sizeof(line), in)) {
        struct inpcb    pcb, *nnew;
        static int      linux_states[12] =
            { 1, 5, 3, 4, 6, 7, 11, 1, 8, 9, 2, 10 };
        unsigned int    lp, fp;
        int             state, uid;

        if (6 != sscanf(line,
                        "%*d: %x:%x %x:%x %x %*X:%*X %*X:%*X %*X %d",
                        &pcb.inp_laddr.s_addr, &lp,
                        &pcb.inp_faddr.s_addr, &fp, &state, &uid))
            continue;

        pcb.inp_lport = htons((unsigned short) lp);
        pcb.inp_fport = htons((unsigned short) fp);

        pcb.inp_state = (state & 0xf) < 12 ? linux_states[state & 0xf] : 2;
        if (pcb.inp_state == 5  ||
            pcb.inp_state == 8  )
            tcp_estab++;
        pcb.uid = uid;

        nnew = SNMP_MALLOC_TYPEDEF(struct inpcb);
        if (nnew == NULL)
            break;
        memcpy(nnew, &pcb, sizeof(struct inpcb));
        nnew->inp_next = tcp_head;
        tcp_head       = nnew;
    }

    fclose(in);

    DEBUGMSGTL(("mibII/tcpTable", "Loaded TCP Table (linux)\n"));
    return 0;
}
