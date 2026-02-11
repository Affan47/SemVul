read_chunk_moov(qtmovie_t *qtmovie, size_t chunk_len)
{
    size_t size_remaining = chunk_len - 8;

    while (size_remaining)
    {
        size_t sub_chunk_len;
        fourcc_t sub_chunk_id;

        sub_chunk_len = stream_read_uint32(qtmovie->stream);
        if (sub_chunk_len <= 1 || sub_chunk_len > size_remaining)
        {
            fprintf(stderr, "strange size for chunk inside moov\n");
            return 0;
        }

        sub_chunk_id = stream_read_uint32(qtmovie->stream);

        switch (sub_chunk_id)
        {
        case MAKEFOURCC('m','v','h','d'):
            read_chunk_mvhd(qtmovie, sub_chunk_len);
            break;
        case MAKEFOURCC('t','r','a','k'):
            if (read_chunk_trak(qtmovie, sub_chunk_len) == 0)
                return 0;
            break;
        case MAKEFOURCC('u','d','t','a'):
            read_chunk_udta(qtmovie, sub_chunk_len);
            break;
        case MAKEFOURCC('e','l','s','t'):
            read_chunk_elst(qtmovie, sub_chunk_len);
            break;
        case MAKEFOURCC('i','o','d','s'):
            read_chunk_iods(qtmovie, sub_chunk_len);
            break;
        default:
            fprintf(stderr, "(moov) unknown chunk id: %c%c%c%c\n",
                    SPLITFOURCC(sub_chunk_id));
            return 0;
        }

        size_remaining -= sub_chunk_len;
    }

    return 1;
}
