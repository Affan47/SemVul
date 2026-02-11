send_msg(const struct atmsvc_msg *msg)
{
    int wrote;

    wrote = write(sock,msg,sizeof(*msg));
    if (wrote == sizeof(*msg)) return;
    if (wrote < 0) perror("write");
    else fprintf(stderr,"bad write: %d != %d\n",wrote,sizeof(*msg));
    exit(1);
}
