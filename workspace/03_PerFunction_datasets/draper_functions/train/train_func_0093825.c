add(QObject *o) {
        QMutexLocker locker(&m_mutex);
        try {
            manage(o);
        } catch (NoUriException) {


        }
        DEBUG << "ObjectMapper::add: Adding " << o << " to changed list" << endl;
        m_changedObjects.insert(o);
    }
