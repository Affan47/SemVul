setDocumentName(Print::Printer *p) const
{
    QString tmp;
    if (patient())
        tmp = patient()->data(Core::IPatient::FullName).toString().replace(" ", "_");
    p->printer()->setDocName(QString("%1-%2").arg(qApp->applicationName(), tmp.leftJustified(50,'_')));
}
