read(FILE* stream, const char* delimiter, size_t bufsize) {

 if (readbuf==NULL) {
    GMALLOC(readbuf, bufsize);
    readbufsize=bufsize;
    }
  else if (bufsize!=readbufsize) {
            GFREE(readbuf);
            if (bufsize>0) {
              GMALLOC(readbuf, bufsize);
              }
            readbufsize=bufsize;
            }
 if (bufsize==0) {
    replace_data(0);
    return 0;
    }
 size_t numread;
 size_t acc_len=0;
 int seplen=strlen(delimiter);
 void* p=NULL;
 Data *data = new_data(0);
 do {
   numread=fread(readbuf, 1, bufsize, stream);
   if (numread) {
     p=Gmemscan(readbuf, bufsize, (void*) delimiter, seplen);
     if (p!=NULL) {

           int l = (char*)p-(char*)readbuf;
           fseek(stream, l+seplen-numread, SEEK_CUR);
           numread=l+seplen;
           }
        else {
           if (numread==bufsize) {
               fseek(stream, -seplen, SEEK_CUR);
               numread-=seplen;
               }
           }
      if (data==&null_data) {
        data=new_data(numread);
        ::memcpy(data->chars, readbuf, numread);
        acc_len+=numread;
        }
       else {
        GREALLOC(data, sizeof(Data)+acc_len+numread);
        memcpy(&data->chars[acc_len], readbuf, numread);
        acc_len+=numread;
        data->length=acc_len;
        data->chars[acc_len]='\0';
        }
      }
   } while (p==NULL && numread!=0);
  replace_data(data);
  return acc_len;
}
