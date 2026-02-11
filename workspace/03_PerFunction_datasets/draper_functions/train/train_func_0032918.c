fileChangedOnDisk()
{
    LOG(logDEBUG) << "signalFileChanged";

    fileWatcher_.removeFile( file_->fileName() );

    const QString name = file_->fileName();
    QFileInfo info( name );

    LogDataOperation* newOperation = NULL;

    LOG(logDEBUG) << "current fileSize=" << fileSize_;
    LOG(logDEBUG) << "info file_->size()=" << info.size();
    if ( info.size() < fileSize_ ) {
        fileChangedOnDisk_ = Truncated;
        LOG(logINFO) << "File truncated";
        newOperation = new FullIndexOperation();
    }
    else if ( fileChangedOnDisk_ != DataAdded ) {
        fileChangedOnDisk_ = DataAdded;
        LOG(logINFO) << "New data on disk";
        newOperation = new PartialIndexOperation( fileSize_ );
    }

    if ( newOperation )
        enqueueOperation( newOperation );

    lastModifiedDate_ = info.lastModified();

    emit fileChanged( fileChangedOnDisk_ );

}
