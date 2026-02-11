unmanage(QObjectList ol) {
        foreach (QObject *o, ol) {
            unmanage(o);
        }
    }
