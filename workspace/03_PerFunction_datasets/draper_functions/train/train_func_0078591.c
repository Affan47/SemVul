read_chunk_ftyp(qtmovie_t *qtmovie, size_t chunk_len)
{
    fourcc_t type;
    uint32_t minor_ver;
    size_t size_remaining = chunk_len - 8;

    type = stream_read_uint32(qtmovie->stream);
    size_remaining-=4;
    if (type != MAKEFOURCC('M','4','A',' '))
    {
        fprintf(stderr, "not M4A file\n");
        return;
    }
    minor_ver = stream_read_uint32(qtmovie->stream);
    size_remaining-=4;


    while (size_remaining)
    {

         stream_read_uint32(qtmovie->stream);
        size_remaining-=4;
    }
}
