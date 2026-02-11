sfsetfd(reg Sfio_t * f, reg int newfd)
#else
int sfsetfd(f, newfd)
reg Sfio_t *f;
reg int newfd;
#endif
{
    reg int oldfd;

    SFMTXSTART(f, -1);

    if (f->flags & SF_STRING)
	SFMTXRETURN(f, -1);

    if ((f->mode & SF_INIT) && f->file < 0) {
	if (newfd < 0)
	    SFMTXRETURN(f, -1);
    } else {
	if ((f->mode & SF_RDWR) != f->mode && _sfmode(f, 0, 0) < 0)
	    SFMTXRETURN(f, -1);
	SFLOCK(f, 0);

	oldfd = f->file;
	if (oldfd >= 0) {
	    if (newfd >= 0) {
		if ((newfd = _sfdup(oldfd, newfd)) < 0) {
		    SFOPEN(f, 0);
		    SFMTXRETURN(f, -1);
		}
		CLOSE(oldfd);
	    } else {
		if (((f->mode & SF_WRITE) && f->next > f->data) ||
		    (f->mode & SF_READ) || f->disc == _Sfudisc) {
		    if (SFSYNC(f) < 0) {
			SFOPEN(f, 0);
			SFMTXRETURN(f, -1);
		    }
		}

		if (((f->mode & SF_WRITE) && f->next > f->data) ||
		    ((f->mode & SF_READ) && f->extent < 0 &&
		     f->next < f->endb)) {
		    SFOPEN(f, 0);
		    SFMTXRETURN(f, -1);
		}
#ifdef MAP_TYPE
		if ((f->bits & SF_MMAP) && f->data) {
		    SFMUNMAP(f, f->data, f->endb - f->data);
		    f->data = NIL(uchar *);
		}
#endif


		f->endb = f->endr = f->endw = f->data;
		f->extent = f->here = 0;
		f->mode = (f->mode & SF_RDWR) | SF_INIT;
		f->bits &= ~SF_NULL;
	    }
	}

	SFOPEN(f, 0);
    }


    if (_Sfnotify)
	(*_Sfnotify) (f, SF_SETFD, newfd);

    f->file = newfd;

    SFMTXRETURN(f, newfd);
}
