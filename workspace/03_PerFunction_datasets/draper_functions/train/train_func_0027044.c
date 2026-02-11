sendpack_eth(char *device, int atsock,
		u_char *frame, int frame_length) {
    struct sockaddr     sa;
    int                 sendBytes;

    memset(&sa,0,sizeof(sa));
    strncpy(sa.sa_data,device,sizeof(sa.sa_data));

    sendBytes=sendto(atsock,frame,frame_length,0,&sa,sizeof(sa));
    if (sendBytes<0) {
        perror("send_ethernet_frame(): sendto");
        return (-1);
    } else if (sendBytes<frame_length) {
#ifdef __DEBUG__
        fprintf(stderr,"send_ethernet_frame(): "
                "WARNING: short send %d out off %d\n",sendBytes,frame_length);
#endif
    }

    return sendBytes;
}
