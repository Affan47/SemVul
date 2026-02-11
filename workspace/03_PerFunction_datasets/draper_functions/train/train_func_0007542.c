highestVersionPack(const QString &packUuid)
    {
        Utils::VersionNumber highest("0.0.0");
        int id = -1;
        for(int i=0; i < m_AvailPacks.count(); ++i) {
            const Pack &p = m_AvailPacks.at(i);
            if (p.uuid() == packUuid) {

                Utils::VersionNumber testing(p.version());

                if (testing > highest) {
                    highest = testing;
                    id = i;
                }
            }
        }
        return id;
    }
