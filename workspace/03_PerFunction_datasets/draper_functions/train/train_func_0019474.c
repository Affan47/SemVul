mgopengl_sharectx(void)
{
  mgcontext *another;
  GLXContext shareable = NULL;
  for(another = _mgclist; another != NULL; another = another->next) {
    if(another->devno == MGD_OPENGL) {
      if((shareable = ((mgopenglcontext *)another)->cam_ctx[SGL]) != NULL
	 || (shareable = ((mgopenglcontext *)another)->cam_ctx[DBL]) != NULL)
	break;
    }
  }
  return shareable;
}
