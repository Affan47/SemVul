v5dOpenFile(const char *filename, v5dstruct * v)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {

	return 0;
    }

    if (v) {
	v5dInitStruct(v);
    }
    else {
	v = v5dNewStruct();
	if (!v) {
	    return NULL;
	}
    }

    v->FileDesc = fd;
    v->Mode = 'r';
    if (read_v5d_header(v)) {
	return v;
    }
    else {
	return NULL;
    }
}
