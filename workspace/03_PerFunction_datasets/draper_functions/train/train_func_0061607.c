doStart(
        LogDataWorkerThread& workerThread ) const
{
    LOG(logDEBUG) << "Attaching " << filename_.toStdString();
    workerThread.attachFile( filename_ );
    workerThread.indexAll();
}
