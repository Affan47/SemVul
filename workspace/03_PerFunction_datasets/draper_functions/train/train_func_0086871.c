symlink( const QString& target, const KUrl & dest, JobFlags flags )
{

    KIO_ARGS << target << dest << (qint8) (flags & Overwrite);
    return SimpleJobPrivate::newJob(dest, CMD_SYMLINK, packedArgs, flags);
}
