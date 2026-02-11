gen_ether_linktype(proto)
     register int proto;
{
    struct block *b0, *b1;

    switch (proto)
    {

        case LLCSAP_ISONS:
        case LLCSAP_IP:
        case LLCSAP_NETBEUI:


            b0 = gen_cmp_gt(OR_LINK, off_linktype, BPF_H, ETHERMTU);
            gen_not(b0);
            b1 = gen_cmp(OR_MACPL, 0, BPF_H, (bpf_int32) ((proto << 8) | proto));
            gen_and(b0, b1);
            return b1;

        case LLCSAP_IPX:


            b0 = gen_cmp(OR_MACPL, 0, BPF_B, (bpf_int32) LLCSAP_IPX);
            b1 = gen_cmp(OR_MACPL, 0, BPF_H, (bpf_int32) 0xFFFF);
            gen_or(b0, b1);


            b0 = gen_snap(0x000000, ETHERTYPE_IPX);
            gen_or(b0, b1);


            b0 = gen_cmp_gt(OR_LINK, off_linktype, BPF_H, ETHERMTU);
            gen_not(b0);


            gen_and(b0, b1);


            b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, (bpf_int32) ETHERTYPE_IPX);
            gen_or(b0, b1);
            return b1;

        case ETHERTYPE_ATALK:
        case ETHERTYPE_AARP:


            b0 = gen_cmp_gt(OR_LINK, off_linktype, BPF_H, ETHERMTU);
            gen_not(b0);


            if (proto == ETHERTYPE_ATALK)
                b1 = gen_snap(0x080007, ETHERTYPE_ATALK);
            else
                b1 = gen_snap(0x000000, ETHERTYPE_AARP);
            gen_and(b0, b1);


            b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, (bpf_int32) proto);

            gen_or(b0, b1);
            return b1;

        default:
            if (proto <= ETHERMTU)
            {


                b0 = gen_cmp_gt(OR_LINK, off_linktype, BPF_H, ETHERMTU);
                gen_not(b0);
                b1 = gen_cmp(OR_LINK, off_linktype + 2, BPF_B, (bpf_int32) proto);
                gen_and(b0, b1);
                return b1;
            }
            else
            {


                return gen_cmp(OR_LINK, off_linktype, BPF_H, (bpf_int32) proto);
            }
    }
}
