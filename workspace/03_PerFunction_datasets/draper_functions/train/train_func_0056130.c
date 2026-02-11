delNonPasswordStorableSite(const QString& host)
{
    if (!d->formCompletions) {
        d->formCompletions = new KConfig(KStandardDirs::locateLocal("data", "khtml/formcompletions"));
    }

    KConfigGroup cg( d->formCompletions, "NonPasswordStorableSites");
    QStringList sites = cg.readEntry("Sites", QStringList());
    sites.removeOne(host);
    cg.writeEntry("Sites", sites);
    cg.sync();
}
