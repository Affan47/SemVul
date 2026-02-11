startsDosageTransmission()
{
    connect(&d->m_Sender, SIGNAL(sent()), this, SLOT(dosageTransmissionDone()));
    d->m_Data = protocolsBase().getDosageToTransmit();
    if (d->m_Data.count()==0) {
        return false;
    }
    QStringList list = d->m_Data.values();
    d->m_Sender.setMessage(list.join("\n\n"));
    d->m_Sender.setUser(qApp->applicationName() + " - " + qApp->applicationVersion());
    d->m_Sender.setTypeOfMessage(Utils::MessageSender::DosageTransmission);
    d->m_Sender.postMessage();
    return true;
}
