printIPPart(unsigned char *ip){

    printf("Packet is: \n");
    for(int i=0;i<100;i++){
        printf("%02x-",ip[i]);
    }
}
