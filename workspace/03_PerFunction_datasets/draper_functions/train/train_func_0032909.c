print_send(OUT *out,int in_link,const struct atmtcp_hdr *hdr,
  int size)
{
    int length = ntohl(hdr->length);
    int i;

    printf("Link %d (from link %d), VPI %d, VCI %d, %d byte%s:",out->link,
      in_link,ntohs(hdr->vpi),ntohs(hdr->vci),length,length == 1 ? "" : "s");
    for (i = 0; i < length; i++) {
	if (!(i & 15)) printf("\n ");
	printf(" %02x",((unsigned char *) (hdr+1))[i]);
    }
    putchar('\n');
    fflush(stdout);
}
