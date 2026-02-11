finishOperation(const QString& msg)
{
    statusBar()->showMessage(msg + tr(" (%1 s.)").arg(m_operationTime.elapsed() / 100 / 10.0));
    statusBar()->removeWidget(m_progressBar);
}
