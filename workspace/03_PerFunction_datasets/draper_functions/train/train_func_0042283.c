bufFree(dataBufType *inf)
{
    if (inf->dataLen) {
	syslog(LOG_ERR,"Freeing buffer with %d byte(s) data", inf->dataLen);
    }
    MUNMAP_IF_SET(inf->bufStart,inf->bufSize);
    inf->bufStart=inf->dataStart=NULL;
    inf->bufSize=inf->dataLen=0;
}
