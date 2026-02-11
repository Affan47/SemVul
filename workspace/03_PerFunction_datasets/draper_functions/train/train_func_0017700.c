onUploadProgress( int percentage )
{
    uiProgress.progressBar->setValue( percentage );
    uiProgress.bottomLabel->setText( tr("Sending your listening history to Last.fm") );
}
