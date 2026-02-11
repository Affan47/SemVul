fsp_fwrite(const void * source, size_t size, size_t count, FSP_FILE * file)
{
    size_t total,done,freebytes;
    const char *ptr;

    if(file->eof || file->err)
        return 0;

    file->out.len=FSP_SPACE;
    total=count*size;
    done=0;
    ptr=source;

    while(1)
    {

        if(file->bufpos>=FSP_SPACE)
        {

            file->out.pos=file->pos;
            if(fsp_transaction(file->s,&file->out,&file->in))
            {
                 file->err=1;
                 return done/size;
            }
            if(file->in.cmd == FSP_CC_ERR)
            {
                errno = EIO;
                file->err=1;
                return done/size;
            }
            file->bufpos=0;
            file->pos+=file->out.len;
            done+=file->out.len;
        }
        freebytes=FSP_SPACE - file->bufpos;

        if(freebytes <= total )
        {

            memcpy(file->out.buf+file->bufpos,ptr,freebytes);
            ptr+=freebytes;
            file->bufpos=FSP_SPACE;
            total-=freebytes;
        } else
        {

            memcpy(file->out.buf+file->bufpos,ptr,total);
            file->bufpos+=total;
            errno = 0;
            return count;
        }
    }
}
