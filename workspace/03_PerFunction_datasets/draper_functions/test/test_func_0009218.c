closeArchive() {
    d->dirList.clear();

    bool ok = true;


    if (d->tmpFile && (mode() & QIODevice::WriteOnly)) {
        ok = d->writeBackTempFile( fileName() );
        delete d->tmpFile;
        d->tmpFile = 0;
        setDevice(0);
    }

    return ok;
}
