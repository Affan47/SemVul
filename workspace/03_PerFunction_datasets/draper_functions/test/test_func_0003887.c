read_frame(BVID_DemuxContext *vid, ByteIOContext *pb, AVPacket *pkt,
                      uint8_t block_type, AVFormatContext *s, int npixels)
{
    uint8_t * vidbuf_start = NULL;
    int vidbuf_nbytes = 0;
    int code;
    int bytes_copied = 0;
    int position;
    unsigned int vidbuf_capacity;

    vidbuf_start = av_malloc(vidbuf_capacity = BUFFER_PADDING_SIZE);
    if(!vidbuf_start)
        return AVERROR(ENOMEM);


    position = url_ftell(pb) - 1;

    vidbuf_start[vidbuf_nbytes++] = block_type;


    vid->video_pts += vid->bethsoft_global_delay + get_le16(pb);


    if(block_type == VIDEO_YOFF_P_FRAME){
        if(get_buffer(pb, &vidbuf_start[vidbuf_nbytes], 2) != 2)
            goto fail;
        vidbuf_nbytes += 2;
    }

    do{
        vidbuf_start = av_fast_realloc(vidbuf_start, &vidbuf_capacity, vidbuf_nbytes + BUFFER_PADDING_SIZE);
        if(!vidbuf_start)
            return AVERROR(ENOMEM);

        code = get_byte(pb);
        vidbuf_start[vidbuf_nbytes++] = code;

        if(code >= 0x80){
            if(block_type == VIDEO_I_FRAME)
                vidbuf_start[vidbuf_nbytes++] = get_byte(pb);
        } else if(code){
            if(get_buffer(pb, &vidbuf_start[vidbuf_nbytes], code) != code)
                goto fail;
            vidbuf_nbytes += code;
        }
        bytes_copied += code & 0x7F;
        if(bytes_copied == npixels){

            if(get_byte(pb))
                url_fseek(pb, -1, SEEK_CUR);
            break;
        }
        if(bytes_copied > npixels)
            goto fail;
    } while(code);


    if(av_new_packet(pkt, vidbuf_nbytes) < 0)
        goto fail;
    memcpy(pkt->data, vidbuf_start, vidbuf_nbytes);
    av_free(vidbuf_start);

    pkt->pos = position;
    pkt->stream_index = 0;
    pkt->pts = vid->video_pts;

    vid->nframes--;
    return vidbuf_nbytes;
fail:
    av_free(vidbuf_start);
    return -1;
}
