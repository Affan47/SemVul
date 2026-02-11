ff_interleave_add_packet(AVFormatContext *s, AVPacket *pkt,
                              int (*compare)(AVFormatContext *, AVPacket *, AVPacket *))
{
    AVPacketList **next_point, *this_pktl;

    this_pktl = av_mallocz(sizeof(AVPacketList));
    this_pktl->pkt= *pkt;
    if(pkt->destruct == av_destruct_packet)
        pkt->destruct= NULL;
    else
        av_dup_packet(&this_pktl->pkt);

    next_point = &s->packet_buffer;
    while(*next_point){
        if(compare(s, &(*next_point)->pkt, pkt))
            break;
        next_point= &(*next_point)->next;
    }
    this_pktl->next= *next_point;
    *next_point= this_pktl;
}
