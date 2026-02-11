print(const QTextDocument &text, const int papers, bool printDuplicata) const
{
    Print::Printer p;

    if (!p.getUserPrinter()) {
        QPrinter *print = new QPrinter;
        print->setResolution(QPrinter::ScreenResolution);
        p.setPrinter(print);
    }

    setDocumentName(&p);
    prepareHeader(&p, papers);
    prepareFooter(&p, papers);
    prepareWatermark(&p, papers);


        p.setContent(text);


    p.setPrintWithDuplicata(printDuplicata);

    if (!p.preparePages()) {
        LOG_ERROR("Prepare pages process is wrong");
    }

    QWidget *parent = qApp->activeModalWidget();
    if (!parent)
        parent = Core::ICore::instance()->mainWindow();
    Internal::PrintDialog dlg(parent);
    dlg.setWindowModality(Qt::WindowModal);
    dlg.setPrinter(&p);
    int r = dlg.exec();
    if (r==QDialog::Accepted)
        return true;
    return false;
}
