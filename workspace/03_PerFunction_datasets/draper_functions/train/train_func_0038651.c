fsp_fseek(FSP_FILE *stream, long offset, int whence)
{
    long newoffset;

    switch(whence)
    {
        case SEEK_SET:
                      newoffset = offset;
                      break;
        case SEEK_CUR:
                      newoffset = stream->pos + offset;
                      break;
        case SEEK_END:
                      errno = ENOTSUP;
                      return -1;
        default:
                      errno = EINVAL;
                      return -1;
    }
    if(stream->writing)
    {
        if(fsp_fflush(stream))
        {
            return -1;
        }
    }
    stream->pos=newoffset;
    stream->eof=0;
    fsp_fpurge(stream);
    return 0;
}
