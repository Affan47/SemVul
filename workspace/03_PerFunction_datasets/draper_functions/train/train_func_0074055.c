supported(FXApp* application,int& major,int& minor){
  major=minor=0;
  if(application->isInitialized()){
#ifdef HAVE_GL_H
#ifndef WIN32
    if(!glXQueryExtension(DISPLAY(application),NULL,NULL)) return FALSE;
    if(!glXQueryVersion(DISPLAY(application),&major,&minor)) return FALSE;
#if GL_VERSION_1_5
    if(minor>5) minor=5;
#elif GL_VERSION_1_4
    if(minor>4) minor=4;
#elif GL_VERSION_1_3
    if(minor>3) minor=3;
#elif GL_VERSION_1_2
    if(minor>2) minor=2;
#elif GL_VERSION_1_1
    if(minor>1) minor=1;
#else
    if(minor>0) minor=0;
#endif
    return TRUE;
#else
    major=1;
#if GL_VERSION_1_4
    minor=4;
#elif GL_VERSION_1_3
    minor=3;
#elif GL_VERSION_1_2
    minor=2;
#elif GL_VERSION_1_1
    minor=1;
#else
    minor=0;
#endif
    return TRUE;
#endif
#endif
    }
  return FALSE;
  }
