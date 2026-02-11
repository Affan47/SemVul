p12u_WriteToExportFile(void *arg, const char *buf, unsigned long len) {
    p12uContext* p12cxt = (p12uContext*)arg;
    int writeLen;

    if(!p12cxt || (p12cxt->error == PR_TRUE)) return;
    if(p12cxt->file == NULL) {
      NSSUtilLogger.msg(ERROR, "p12 file is empty");
      p12cxt->error = PR_TRUE;
      return;
    }
    writeLen = PR_Write(p12cxt->file, (unsigned char *)buf, (int32)len);
    if(writeLen != (int)len) {
      PR_Close(p12cxt->file);
      PR_Free(p12cxt->filename);
      p12cxt->filename = NULL;
      p12cxt->file = NULL;
      NSSUtilLogger.msg(ERROR, "Unable to write to p12 file");
      p12cxt->error = PR_TRUE;
    }
  }
