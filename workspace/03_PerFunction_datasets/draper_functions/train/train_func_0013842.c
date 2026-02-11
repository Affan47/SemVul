readData(char *data, qint64 maxSize)
{
    int read = 0;
    while(read < maxSize)
    {
        if(d->inBufPos == d->inBufSize)
        {
            d->inBufPos = 0;
            d->inBufSize = d->io->read(d->inBuf, QUAZIO_INBUFSIZE);
            if(d->inBufSize == -1)
            {
                d->inBufSize = 0;
                setErrorString(d->io->errorString());
                return -1;
            }
            if(d->inBufSize == 0)
            {
                break;
            }
        }
        while(read < maxSize && d->inBufPos < d->inBufSize)
        {
            d->zins.next_in = (Bytef *)(d->inBuf + d->inBufPos);
            d->zins.avail_in = d->inBufSize - d->inBufPos;
            d->zins.next_out = (Bytef *)(data + read);
            d->zins.avail_out = (uInt)(maxSize - read);
            int more = 0;
            switch(inflate(&d->zins, Z_SYNC_FLUSH))
            {
            case Z_OK:
                read = (char *) d->zins.next_out - data;
                d->inBufPos = (char *) d->zins.next_in - d->inBuf;
                break;
            case Z_STREAM_END:
                read = (char *) d->zins.next_out - data;
                d->inBufPos = (char *) d->zins.next_in - d->inBuf;
                return read;
            case Z_BUF_ERROR:
                if(!d->zBufError)
                {
                    qWarning("Z_BUF_ERROR detected with %d/%d in/out, weird",
                             d->zins.avail_in, d->zins.avail_out);
                    d->zBufError = true;
                }
                memmove(d->inBuf, d->inBuf + d->inBufPos, d->inBufSize - d->inBufPos);
                d->inBufSize -= d->inBufPos;
                d->inBufPos = 0;
                more = d->io->read(d->inBuf + d->inBufSize, QUAZIO_INBUFSIZE - d->inBufSize);
                if(more == -1)
                {
                    setErrorString(d->io->errorString());
                    return -1;
                }
                if(more == 0)
                {
                    return read;
                }
                d->inBufSize += more;
                break;
            default:
                setErrorString(QString::fromLocal8Bit(d->zins.msg));
                return -1;
            }
        }
    }
#ifdef QUAZIP_ZIODEVICE_DEBUG_INPUT
    indebug.write(data, read);
#endif
    return read;
}
