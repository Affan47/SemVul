ShmAttach(int imageWidth, int imageHeight)
{
  if (_useShm) {
    _XImage = XShmCreateImage(_display, _XVInfo.visual, _depth, ZPixmap, NULL, &_XShmInfo, imageWidth, imageHeight);
    if (_XImage == NULL) {
      PTRACE(1, "X11\tXShmCreateImage failed");
      _useShm = FALSE;
    }
  }

  if (_useShm) {
    _XShmInfo.shmid = shmget(IPC_PRIVATE, _XImage->bytes_per_line * _XImage->height, IPC_CREAT | 0777);
    if (_XShmInfo.shmid < 0) {
       XDestroyImage(_XImage);
       _XImage = NULL;
       PTRACE(1, "X11\tshmget failed");
       _useShm = FALSE;
    }
  }

  if (_useShm) {
    _XShmInfo.shmaddr = (char *) shmat(_XShmInfo.shmid, 0, 0);
    if (_XShmInfo.shmaddr == ((char *) -1)) {
      XDestroyImage(_XImage);
      _XImage = NULL;
      PTRACE(1, "X11\tshmat failed");
      _useShm = FALSE;
    }
  }

  if (_useShm) {
    _XImage->data = _XShmInfo.shmaddr;
    _XShmInfo.readOnly = False;


    XErrorHandler oldHandler = XSetErrorHandler((XErrorHandler) catchXShmError);
    Status status = XShmAttach (_display, &_XShmInfo);
    XSync(_display, False);
    XSetErrorHandler((XErrorHandler) oldHandler);

    if ( (status != True) || (_shmError) ) {
      XDestroyImage(_XImage);
      _XImage = NULL;
      if (_XShmInfo.shmaddr != ((char *) -1)) {
        shmdt(_XShmInfo.shmaddr);
      }
      PTRACE(1, "X11\t  XShmAttach failed");
      if ( (status == True) && (_shmError) ) {
        PTRACE(1, "X11\t  X server supports SHM but apparently we are remotely connected...");
      }
      _useShm = false;
    }
  }

  if (_useShm) {
    shmctl(_XShmInfo.shmid, IPC_RMID, 0);
  }
}
