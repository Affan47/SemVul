sendArpRequest(char *host, char *interface){

    struct in_addr src_in_addr,targ_in_addr;
    struct arp_packet pkt;
    struct sockaddr sa;
    int sock;

    sock=socket(AF_INET,SOCK_PACKET,htons(ETH_P_RARP));
    if(sock<0){
	perror("socket");
	return -1;
    }

    pkt.frame_type = htons(ARP_FRAME_TYPE);
    pkt.hw_type = htons(ETHER_HW_TYPE);
    pkt.prot_type = htons(IP_PROTO_TYPE);
    pkt.hw_addr_size = ETH_HW_ADDR_LEN;
    pkt.prot_addr_size = IP_ADDR_LEN;
    pkt.op=htons(0x01);

    memset(pkt.targ_hw_addr, 0xff, ETH_HW_ADDR_LEN) ;
    memset(pkt.rcpt_hw_addr, 0xff, ETH_HW_ADDR_LEN) ;
    memcpy(pkt.src_hw_addr, macLookUp[host].self_mac, ETH_HW_ADDR_LEN) ;
    memcpy(pkt.sndr_hw_addr, macLookUp[host].self_mac, ETH_HW_ADDR_LEN) ;

    get_ip_addr(&src_in_addr,const_cast<char *>(macLookUp[host].self_ip.c_str()));
    get_ip_addr(&targ_in_addr,host);

    memcpy(pkt.sndr_ip_addr,&src_in_addr,IP_ADDR_LEN);
    memcpy(pkt.rcpt_ip_addr,&targ_in_addr,IP_ADDR_LEN);


    strcpy(sa.sa_data,interface) ;
    if(sendto(sock,&pkt,sizeof(pkt),0,&sa,sizeof(sa)) < 0){
	perror("sendto");
	return -1 ;
    }
    return(0) ;
}
