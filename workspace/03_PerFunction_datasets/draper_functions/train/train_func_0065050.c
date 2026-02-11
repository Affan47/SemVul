readFile( const QString& fileName, int )
{
    QFileInfo fileInfo( fileName );
    if ( fileInfo.isReadable() )
    {
        LOG(logDEBUG) << "Entering readFile " << fileName.toStdString();


        stopLoading();


        replaceCurrentSearch( "" );
        logFilteredData_->clearMarks();
        logData_->attachFile( fileName );
        logMainView->updateData();


        return true;
    }
    else {
        return false;
    }
}
