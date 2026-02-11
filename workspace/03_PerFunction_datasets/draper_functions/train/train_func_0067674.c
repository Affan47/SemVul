connectNotify(const char *signal)
{

    if (!d_ptr->isConnected) {
        if (d_ptr->engine) {
            if (QLatin1String(signal) == SIGNAL(landmarksAdded(QList<QLandmarkId>))
                || (QLatin1String(signal) == SIGNAL(landmarksChanged(QList<QLandmarkId>)))
                || (QLatin1String(signal) == SIGNAL(landmarksRemoved(QList<QLandmarkId>)))
                || (QLatin1String(signal) == SIGNAL(landmarksChanged(QList<QLandmarkId>)))
                || (QLatin1String(signal) == SIGNAL(categoriesAdded(QList<QLandmarkCategoryId>)))
                || (QLatin1String(signal) == SIGNAL(categoriesChanged(QList<QLandmarkCategoryId>)))
                || (QLatin1String(signal) == SIGNAL(categoriesRemoved(QList<QLandmarkCategoryId>)))
                || (QLatin1String(signal) == SIGNAL(dataChanged()))) {
                connect(d_ptr->engine,SIGNAL(landmarksAdded(QList<QLandmarkId>)),
                        this, SIGNAL(landmarksAdded(QList<QLandmarkId>)));
                connect(d_ptr->engine,SIGNAL(landmarksChanged(QList<QLandmarkId>)),
                        this, SIGNAL(landmarksChanged(QList<QLandmarkId>)));
                connect(d_ptr->engine,SIGNAL(landmarksRemoved(QList<QLandmarkId>)),
                        this, SIGNAL(landmarksRemoved(QList<QLandmarkId>)));
                connect(d_ptr->engine,SIGNAL(categoriesAdded(QList<QLandmarkCategoryId>)),
                        this, SIGNAL(categoriesAdded(QList<QLandmarkCategoryId>)));
                connect(d_ptr->engine,SIGNAL(categoriesChanged(QList<QLandmarkCategoryId>)),
                        this, SIGNAL(categoriesChanged(QList<QLandmarkCategoryId>)));
                connect(d_ptr->engine,SIGNAL(categoriesRemoved(QList<QLandmarkCategoryId>)),
                        this, SIGNAL(categoriesRemoved(QList<QLandmarkCategoryId>)));
                connect(d_ptr->engine,SIGNAL(dataChanged()),
                        this, SIGNAL(dataChanged()));
                d_ptr->isConnected = true;
            }
        }
    }
    QObject::connectNotify(signal);
}
