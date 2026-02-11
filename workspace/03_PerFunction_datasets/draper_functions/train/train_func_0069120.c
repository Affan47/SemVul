connectEditingEpisodeModels()
    {
        QHashIterator<Form::FormMain *, EpisodeModel *> it(_episodeModels);
        while (it.hasNext()) {
            it.next();

            EpisodeModel *editing = episodeManager().episodeModel(it.key()->uuid());
            if (editing) {
                QObject::connect(editing, SIGNAL(episodeChanged(QModelIndex)), q, SLOT(editingModelEpisodeChanged(QModelIndex)), Qt::UniqueConnection);
                QObject::connect(editing, SIGNAL(rowsInserted(QModelIndex, int, int)), q, SLOT(editingModelRowsInserted(QModelIndex, int, int)), Qt::UniqueConnection);
                QObject::connect(editing, SIGNAL(rowsRemoved(QModelIndex, int, int)), q, SLOT(editingModelRowsRemoved(QModelIndex, int, int)), Qt::UniqueConnection);
            }
        }
    }
