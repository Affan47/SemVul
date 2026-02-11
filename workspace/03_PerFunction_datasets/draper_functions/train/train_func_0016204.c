send_request(struct atmarp_req *req)
{
    struct atmarp_req reply;
    int s,len;

    s = un_attach(ATMARP_SOCKET_PATH);
    if (s < 0) {
	perror("un_attach");
	exit(1);
    }
    if (write(s,req,sizeof(*req)) < 0) {
	perror("write");
	exit(1);
    }
    len = read(s,&reply,sizeof(reply));
    if (len < 0) {
	perror("read");
	exit(1);
    }
    if (req->type == art_query) return query_result(&reply);
    if (len != sizeof(int)) {
	fprintf(stderr,"bad read: %d != %d\n",len,sizeof(int));
	exit(1);
    }
    if (*(int *) &reply < 0) {
	fprintf(stderr,"atmarp: %s\n",strerror(-*(int *) &reply));
	exit(1);
    }
    return *(int *) &reply;
}
