doremovefile(const char *path){
  const char *elem;
  int i;
  if(g_nooper) return;
  for(i = 0; i < cblistnum(g_rmvsufs); i++){
    elem = cblistval(g_rmvsufs, i, NULL);
    if(elem[0] == '\0') continue;
    if(!strcmp(elem, "*") || cbstrbwimatch(path, elem)){
      if(unlink(path) == -1) printferror("%s: could not remove", path);
      break;
    }
  }
}
