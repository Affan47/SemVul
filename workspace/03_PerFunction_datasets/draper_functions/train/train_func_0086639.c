slotCategories(QList<KNS::Category*> categories)
{
    Dxs * dxs = qobject_cast<Dxs*>(sender());
    Provider * provider = dxs->provider();


    for (QList<KNS::Category*>::iterator it = categories.begin(); it != categories.end(); ++it) {
        Category *category = (*it);
        QStringList feeds = provider->feeds();
        for (int i = 0; i < feeds.size(); ++i) {
            dxs->call_entries(category->id(), feeds.at(i));
        }
    }
}
