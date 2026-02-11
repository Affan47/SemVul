freeData(gpointer userData) throw ()
    {
        delete static_cast< boost::shared_ptr<OwnNameAsyncData> *>(userData);
    }
