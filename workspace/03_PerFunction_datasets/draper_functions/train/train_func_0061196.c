accept()
{

    int copies = ui->copies->value();
    m_Printer->printer()->setNumCopies(copies);
    if (ui->allPages->isChecked()) {
        m_Printer->printer()->setPrintRange(QPrinter::AllPages);
    } else {
        m_Printer->printer()->setPrintRange(QPrinter::PageRange);
        m_Printer->printer()->setFromTo(ui->pageFrom->value(), ui->pageTo->value());
    }


    if (!m_Printer->reprint(m_Printer->printer())) {
        LOG_FOR("Printer", "Printing error on device " + m_Printer->printer()->printerName());
        return;
    } else {
        LOG_FOR("Printer", "Printing on device successful" + m_Printer->printer()->printerName());
    }


    if (settings()->value(Constants::S_KEEP_PDF).toBool()) {
        QString uid = Utils::createUid();
        QString docName = QString("%1_%2.pdf")
                          .arg(qApp->applicationName())
                          .arg(uid);

        QString fileName = settings()->value(Constants::S_PDF_FOLDER).toString();
        if (fileName.isEmpty())
            fileName = settings()->path(Core::ISettings::ApplicationTempPath);
        if (QFileInfo(fileName).isRelative())
            fileName.append(qApp->applicationDirPath());
        if (!QDir(fileName).exists())
            QDir().mkpath(fileName);
        fileName.append(QDir::separator() + docName);
        m_Printer->toPdf(fileName, docName);
        docPrinter()->addPrintedDoc(fileName,docName,QDateTime::currentDateTime(), user()->uuid());
    }
    QDialog::accept();
}
