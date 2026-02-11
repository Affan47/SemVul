SearchFile (const char* path, struct stat&) {
    InputFile* f = InputFile::open(path);
    if (f == nil) {
	return;
    }
    const char* buf;
    int len = f->read(buf);
    if (len <= 0) {
	return;
    }
    if (_verbose) {
	printf("searching file %s (%d)\n", path, len);
    }


    char* tbuf = new char[len + 1];
    Memory::copy(buf, tbuf, len);
    tbuf[len] = '\0';

    TextBuffer textbuf(tbuf, len, len);

    SearchTextBuffer(&textbuf, path);

    delete tbuf;
    f->close();
    delete f;
}
