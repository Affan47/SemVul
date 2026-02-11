k5_write_messages(krb5_context context, krb5_pointer fdp, krb5_data *outbuf,
                  int nbufs)
{
    int fd = *( (int *) fdp);

    while (nbufs) {
        int nbufs1;
        sg_buf sg[4];
        krb5_int32 len[2];

        if (nbufs > 1)
            nbufs1 = 2;
        else
            nbufs1 = 1;
        len[0] = htonl(outbuf[0].length);
        SG_SET(&sg[0], &len[0], 4);
        SG_SET(&sg[1], outbuf[0].length ? outbuf[0].data : NULL,
               outbuf[0].length);
        if (nbufs1 == 2) {
            len[1] = htonl(outbuf[1].length);
            SG_SET(&sg[2], &len[1], 4);
            SG_SET(&sg[3], outbuf[1].length ? outbuf[1].data : NULL,
                   outbuf[1].length);
        }
        if (krb5int_net_writev(context, fd, sg, nbufs1 * 2) < 0) {
            return errno;
        }
        outbuf += nbufs1;
        nbufs -= nbufs1;
    }
    return(0);
}
