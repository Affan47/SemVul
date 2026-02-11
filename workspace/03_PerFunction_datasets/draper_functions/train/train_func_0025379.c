GWEN_Directory_CreatePublic(const char *path){

  if (mkdir(path,
            S_IRUSR | S_IWUSR | S_IXUSR
#ifdef S_IRGRP
            | S_IRGRP
#endif
#ifdef S_IXGRP
            | S_IXGRP
#endif
#ifdef S_IROTH
            | S_IROTH
#endif
#ifdef S_IXOTH
            | S_IXOTH
#endif
           )) {
    DBG_INFO(GWEN_LOGDOMAIN, "Error on mkdir(%s): %s",
             path, strerror(errno));
    return -1;
  }
  return 0;
}
