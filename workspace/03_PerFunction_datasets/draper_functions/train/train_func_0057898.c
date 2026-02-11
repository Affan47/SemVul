onProcessFinished(int exitCode)
{
    LOG("PDF Completion finished with exitcode: " + QString::number(exitCode));
    QProcess *process = qobject_cast<QProcess*>(sender());
    Q_ASSERT(process);
    if (!process)
        return;
    if (exitCode) {
        Utils::warningMessageBox(tr("pdftk error"),
                                 tr("The pdftk process ends with the exit code: %1\n"
                                    "%2")
                                 .arg(exitCode)
                                 .arg(QString(process->readAllStandardError())));
    }


    if (process) {
        QProgressDialog *dialog = d->_progressDialog.value(process, 0);
        if (dialog) {
            dialog->setLabelText(tr("Opening completed PDF file"));
            dialog->setValue(1);
        }

        if (!QDesktopServices::openUrl(QUrl("file://" + d->_processOutputFile.value(process))))
            LOG_ERROR("Unable to launch the PDF viewer for the following file: " + d->_processOutputFile.value(d->_process));


        if (!QFile(d->_processTmpFile.value(process)).remove())
            LOG_ERROR("Unable to remove tmp file: " + d->_processTmpFile.value(process));


        d->clearCache(process);
    }


    process->kill();
    process->deleteLater();
}
