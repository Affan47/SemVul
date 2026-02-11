calculateInteractions(const QVector<IDrug *> &drugs)
{
    QTime t;
    t.start();
    d->m_DDIFound.clear();
    d->m_TestedDrugs.clear();
    d->m_Interactions.clear();
    qDeleteAll(d->m_FirstPassInteractions);
    d->m_FirstPassInteractions.clear();
    d->m_TestedDrugs = drugs;
    if (WarnDDIComputation)
        qWarning() << "------------------------------------";
    foreach(IDrug *drug, drugs) {
        checkDrugInteraction(drug, drugs);
    }
    if (d->m_LogChrono)
        Utils::Log::logTimeElapsed(t, "DrugDrugInteractionEngine", QString("interactions(): %1 drugs").arg(drugs.count()));
    if (WarnDDIComputation)
        qWarning() << "------------------------------------";
    return d->m_DDIFound.count();
}
