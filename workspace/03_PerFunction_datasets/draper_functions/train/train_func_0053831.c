fsp_pkt_write(const FSP_PKT *p,void *space)
{
    size_t used;
    unsigned char *ptr;
    int checksum;
    size_t i;

    if(p->xlen + p->len > FSP_SPACE )
    {

        errno = EMSGSIZE;
        return 0;
    }
    ptr=space;

    ptr[FSP_OFFSET_CMD]=p->cmd;
    ptr[FSP_OFFSET_SUM]=0;
    *(uint16_t *)(ptr+FSP_OFFSET_KEY)=htons(p->key);
    *(uint16_t *)(ptr+FSP_OFFSET_SEQ)=htons(p->seq);
    *(uint16_t *)(ptr+FSP_OFFSET_LEN)=htons(p->len);
    *(uint32_t *)(ptr+FSP_OFFSET_POS)=htonl(p->pos);
    used=FSP_HSIZE;

    memcpy(ptr+FSP_HSIZE,p->buf,p->len);
    used+=p->len;

    memcpy(ptr+used,p->buf+p->len,p->xlen);
    used+=p->xlen;

    checksum = 0;
    for(i=0;i<used;i++)
    {
        checksum += ptr[i];
    }
    checksum +=used;
    ptr[FSP_OFFSET_SUM] =  checksum + (checksum >> 8);
    return used;
}
