loaded(ObjectLoader *, ObjectLoader::NodeObjectMap &,
                    Node, QObject *o) {
            DEBUG << "LoadStoreCallback::loaded: Object " << o << endl;
            m_d->manage(o);
        }
