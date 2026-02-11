loadEntries(Provider *provider)
{


    if (m_cachepolicy == CacheOnly) {
        return;
    }


    QStringList feeds = provider->feeds();
    for (int i = 0; i < feeds.count(); i++) {
        Feed *feed = provider->downloadUrlFeed(feeds.at(i));
        if (feed) {
            ++m_activefeeds;

            EntryLoader *entry_loader = new EntryLoader(this);

            connect(entry_loader,
                    SIGNAL(signalEntriesLoaded(KNS::Entry::List)),
                    SLOT(slotEntriesLoaded(KNS::Entry::List)));
            connect(entry_loader,
                    SIGNAL(signalEntriesFailed()),
                    SLOT(slotEntriesFailed()));
            connect(entry_loader,
                    SIGNAL(signalProgress(KJob*,ulong)),
                    SLOT(slotProgress(KJob*,ulong)));

            entry_loader->load(provider, feed);
        }
    }
}
