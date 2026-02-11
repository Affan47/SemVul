fa_mkstemp(std::string& path, mode_t mode) {
    RETRYLOOP {
    STARTHEADER(CMD_TEMPFILE,sizeof(mode)+sizeof(int)+path.length());
    if(!swrite(*file_access_,&mode,sizeof(mode))) ABORTALL;
    if(!swrite_string(*file_access_,path)) ABORTALL;
    int res = 0;
    int l = 0;
    header_t header;
    if(!sread(*file_access_,&header,sizeof(header))) ABORTALL;
    if((header.cmd != CMD_TEMPFILE) || (header.size < (sizeof(res)+sizeof(errno_)+sizeof(int)))) ABORTALL;
    if(!sread(*file_access_,&res,sizeof(res))) ABORTALL;
    if(!sread(*file_access_,&errno_,sizeof(errno_))) ABORTALL;
    if(!sread(*file_access_,&l,sizeof(l))) ABORTALL;
    if((sizeof(res)+sizeof(errno_)+sizeof(l)+l) != header.size) ABORTALL;
    path.assign(l,' ');
    if(!sread(*file_access_,(void*)path.c_str(),l)) ABORTALL;
    return (res != -1);
    }
    errno_ = -1;
    return false;
  }
