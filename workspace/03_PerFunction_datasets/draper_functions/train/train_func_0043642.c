setOrigFileName( const QByteArray & fileName ) {
    if ( !isOpen() || !(mode() & QIODevice::WriteOnly) )
    {
        kWarning(7041) << "KTar::setOrigFileName: File must be opened for writing first.\n";
        return;
    }
    d->origFileName = fileName;
}
