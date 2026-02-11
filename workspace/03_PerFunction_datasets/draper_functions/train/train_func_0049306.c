abort()
{
    if (d->m_bFinished) {
        return;
    }
    kDebug(7010) << this << "m_showingDialog=" << d->m_showingDialog;
    killJob();


    if (d->m_showingDialog) {
        return;
    }
    d->m_bFault = true;
    d->m_bFinished = true;
    d->m_bInit = false;
    d->m_bScanFile = false;


    d->startTimer();
}
