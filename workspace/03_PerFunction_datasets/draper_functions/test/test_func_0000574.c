yuv4_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVStream *st = s->streams[pkt->stream_index];
    ByteIOContext *pb = s->pb;
    AVPicture *picture;
    int* first_pkt = s->priv_data;
    int width, height, h_chroma_shift, v_chroma_shift;
    int i, m;
    char buf2[Y4M_LINE_MAX+1];
    char buf1[20];
    uint8_t *ptr, *ptr1, *ptr2;

    picture = (AVPicture *)pkt->data;


    if (*first_pkt) {
        *first_pkt = 0;
        if (yuv4_generate_header(s, buf2) < 0) {
            av_log(s, AV_LOG_ERROR, "Error. YUV4MPEG stream header write failed.\n");
            return AVERROR(EIO);
        } else {
            put_buffer(pb, buf2, strlen(buf2));
        }
    }


    m = snprintf(buf1, sizeof(buf1), "%s\n", Y4M_FRAME_MAGIC);
    put_buffer(pb, buf1, strlen(buf1));

    width = st->codec->width;
    height = st->codec->height;

    ptr = picture->data[0];
    for(i=0;i<height;i++) {
        put_buffer(pb, ptr, width);
        ptr += picture->linesize[0];
    }

    if (st->codec->pix_fmt != PIX_FMT_GRAY8){

    avcodec_get_chroma_sub_sample(st->codec->pix_fmt, &h_chroma_shift, &v_chroma_shift);
    width >>= h_chroma_shift;
    height >>= v_chroma_shift;

    ptr1 = picture->data[1];
    ptr2 = picture->data[2];
    for(i=0;i<height;i++) {
        put_buffer(pb, ptr1, width);
        ptr1 += picture->linesize[1];
    }
    for(i=0;i<height;i++) {
        put_buffer(pb, ptr2, width);
            ptr2 += picture->linesize[2];
    }
    }
    put_flush_packet(pb);
    return 0;
}
