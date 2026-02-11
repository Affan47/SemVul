areaData(QtMsgType type, unsigned int num, bool enableByDefault = true)
    {
        if (!cache.contains(0)) {

            loadAreaNames();
            Q_ASSERT(cache.contains(0));
        } else if (!m_seenMainComponent && KGlobal::hasMainComponent()) {

            cache[0].name = KGlobal::mainComponent().componentName().toUtf8();
            m_seenMainComponent = true;
        }

        Cache::Iterator it = cache.find(num);
        if (it == cache.end()) {

            Q_ASSERT(cache.contains(0));
            it = cache.find(0);
            num = 0;
        }

        if (num == 0) {
            static bool s_firstDebugFromApplication = true;
            if (s_firstDebugFromApplication && !m_disableAll) {
                s_firstDebugFromApplication = false;

                writeGroupForNamedArea(it->name, enableByDefault);
            }
        }

        const int lev = level(type);

        if (it->mode[lev] == Unknown)
            it->mode[lev] = areaOutputMode(type, num, enableByDefault);
        if (it->mode[lev] == FileOutput && it->logFileName[lev].isEmpty())
            it->logFileName[lev] = logFileName(type, num);

        Q_ASSERT(it->mode[lev] != Unknown);

        return it;
    }
