udata_writeUString(UNewDataMemory *pData, const UChar *s, int32_t length) {
    if(pData!=NULL && pData->file!=NULL) {
        if(length==-1) {
            length=u_strlen(s);
        }
        if(length>0) {
            T_FileStream_write(pData->file, s, length*sizeof(UChar));
        }
    }
}
