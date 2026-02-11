_gio_file_mkdir(GIOControl *gc,char *path) {
    if ( GFileMkDir(path)==-1 ) {
	_GIO_reporterror(gc,errno);
    } else {
	gc->return_code = 201;
	gc->done = true;
	(gc->receivedata)(gc);
    }
}
