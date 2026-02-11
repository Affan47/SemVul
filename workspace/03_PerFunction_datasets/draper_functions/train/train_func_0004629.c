ParseURLAndFillConnection(struct SessionHandle *data,
                                          struct connectdata *conn)
{
  char *at;
  char *tmp;

  char *path = data->reqdata.path;


  if((2 == sscanf(data->change.url, "%15[^:]:%[^\n]",
                  conn->protostr,
                  path)) && strequal(conn->protostr, "file")) {
    if(path[0] == '/' && path[1] == '/') {


      memmove(path, path + 2, strlen(path + 2)+1);
    }


    if(path[0] != '/') {


      char *ptr=strchr(path, '/');
      if(ptr) {


        if(ptr[1] && ('/' == ptr[1]))


          ptr++;


        memmove(path, ptr, strlen(ptr)+1);
      }
    }

    strcpy(conn->protostr, "file");
  }
  else {

    path[0]=0;

    if (2 > sscanf(data->change.url,
                   "%15[^\n:]://%[^\n/]%[^\n]",
                   conn->protostr,
                   conn->host.name, path)) {


      if((1 > sscanf(data->change.url, "%[^\n/]%[^\n]",
                     conn->host.name, path)) ) {


        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }


      if(checkprefix("FTP.", conn->host.name))
        strcpy(conn->protostr, "ftp");
      else if (checkprefix("DICT.", conn->host.name))
        strcpy(conn->protostr, "DICT");
      else if (checkprefix("LDAP.", conn->host.name))
        strcpy(conn->protostr, "LDAP");
      else {
        strcpy(conn->protostr, "http");
      }

      conn->protocol |= PROT_MISSING;
    }
  }


  at = strchr(conn->host.name, '@');
  if(at)
    tmp = strchr(at+1, '?');
  else
    tmp = strchr(conn->host.name, '?');

  if(tmp) {


    size_t hostlen = strlen(tmp);
    size_t pathlen = strlen(path);


    memmove(path+hostlen+1, path, pathlen+1);


    memcpy(path+1, tmp, hostlen);

    path[0]='/';

    *tmp=0;
  }
  else if(!path[0]) {

    strcpy(path, "/");
  }


  if(path[0] == '?') {


    memmove(&path[1], path, strlen(path)+1);
    path[0] = '/';
  }


  return CURLE_OK;
}
