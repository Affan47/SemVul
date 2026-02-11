start_sniffing()
{
    bpf_u_int32 localnet, netmask;
    struct bpf_program fcode;
    char errorbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 defaultnet = 0xFFFFFF00;

    if(readback_mode == 0)
    {
        if(interface == NULL)
        {
            interface = pcap_lookupdev(errorbuf);
            if(interface == NULL)
            {
                fatal("start_sniffing() interface lookup: \n\t%s\n", errorbuf);
            }
        }

        msg("sniffing on interface %s", interface);
        pd = pcap_open_live(interface,
                            snaplen?snaplen:65535,
                            1,
                            500,
                            errorbuf);

        if(pd == NULL)
        {
            fatal("start_sniffing(): interface %s open: %s\n",
                    interface,
                    errorbuf);
        }
    }
    else
    {
        msg("Reading network traffic from \"%s\" file.\n", readfile);
        pd = pcap_open_offline(readfile, errorbuf);
        if(pd == NULL)
        {
            fatal("unable to open file \"%s\" for readback: %s\n",
                  readfile, errorbuf);
        }

        snaplen = pcap_snapshot(pd);
        msg("snaplen = %d\n", snaplen);
    }

    if(pcap_lookupnet(interface, &localnet, &netmask, errorbuf) < 0)
    {
        msg("start_sniffing() device %s network lookup: "
             "\t%s",
             interface,
             errorbuf);

        netmask = htonl(defaultnet);
    }

    if(pcap_compile(pd, &fcode, pcap_cmd, 1, netmask) < 0)
    {
        fatal("start_sniffing() FSM compilation failed: \n\t%s\n"
                "PCAP command: %s\n", pcap_geterr(pd), pcap_cmd);
    }


    if(pcap_setfilter(pd, &fcode) < 0)
    {
        fatal("start_sniffing() setfilter: \n\t%s\n",
                pcap_geterr(pd));
    }


    datalink = pcap_datalink(pd);

    if(datalink < 0)
    {
        fatal("OpenPcap() datalink grab: \n\t%s\n",
                pcap_geterr(pd));
    }
    return 0;
}
