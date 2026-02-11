get_icmp_time_exceeded_response(packetInfo *pi, packetInfo *res){
    struct sniff_ip *ip, *res_ip;
    struct icmphdr *icp;
    ip = (struct sniff_ip*)(pi->packet + SIZE_ETHERNET);
    int size_ip = IP_HL(ip)*4;


    memcpy(res->packet, pi->packet, SIZE_ETHERNET + 20) ;
    res_ip = (struct sniff_ip*)(res->packet + SIZE_ETHERNET);

    res_ip->ip_ttl = 64;

    res_ip->ip_vhl = 0x45 ;

    res_ip->ip_len = htons(20 + size_ip + 8 + 8) ;

    res_ip->ip_p = IPPROTO_ICMP ;

    res_ip->ip_sum = 0 ;

    res_ip->ip_dst = res_ip->ip_src ;
    res_ip->ip_src.s_addr = inet_addr("10.10.0.2") ;

    icp = (struct icmphdr *)(res->packet + SIZE_ETHERNET + 20) ;

    icp->icmp_type = ICMP_TIME_EXCEEDED;

    icp->icmp_code = 0;

    icp->icmp_cksum = 0;
    icp->icmp_seq = 0;
    icp->icmp_id = 0;


    if(pi->len >= SIZE_ETHERNET + size_ip + 8)
	memcpy(res->packet + SIZE_ETHERNET + 20 + 8, pi->packet+SIZE_ETHERNET, size_ip + 8) ;
    else
	memcpy(res->packet + SIZE_ETHERNET + 20 + 8, pi->packet+SIZE_ETHERNET, size_ip) ;
    icp->icmp_cksum = in_cksum((u_short *)icp, res->len - 20 - SIZE_ETHERNET);
}
