_new_CompleteFile(void)
{
  CompleteFile *cf;


  cf = (CompleteFile *) malloc(sizeof(CompleteFile));
  if(!cf) {
    errno = ENOMEM;
    return NULL;
  };


  cf->err = NULL;
  cf->dr = NULL;
  cf->home = NULL;
  cf->path = NULL;
  cf->buff = NULL;
  cf->usrnam[0] = '\0';
  cf->envnam[0] = '\0';


  cf->err = _new_ErrMsg();
  if(!cf->err)
    return _del_CompleteFile(cf);


  cf->dr = _new_DirReader();
  if(!cf->dr)
    return _del_CompleteFile(cf);


  cf->home = _new_HomeDir();
  if(!cf->home)
    return _del_CompleteFile(cf);


  cf->path = _new_PathName();
  if(!cf->path)
    return _del_CompleteFile(cf);


  cf->buff = _new_PathName();
  if(!cf->buff)
    return _del_CompleteFile(cf);
  return cf;
}
