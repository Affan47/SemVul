checkSettingsValidity()
{

    QList<DrugsDB::IDrugEngine *> engines = pluginManager()->getObjects<DrugsDB::IDrugEngine>();
    QStringList uids;
    uids << "__";
    for(int i=0; i < engines.count(); ++i) {
        DrugsDB::IDrugEngine *engine = engines.at(i);
        if (engine->isActiveByDefault())
            uids << engine->uid();
    }

    QHash<QString, QVariant> defaultvalues;
    defaultvalues.insert(DrugsDB::Constants::S_ACTIVATED_INTERACTION_ENGINES, uids);

    foreach(const QString &k, defaultvalues.keys()) {
        if (settings()->value(k).toString().simplified().isEmpty()) {
            LOG("Activating default drugs engines: " + uids.join("; "));
            settings()->setValue(k, defaultvalues.value(k));
        }
    }
}
