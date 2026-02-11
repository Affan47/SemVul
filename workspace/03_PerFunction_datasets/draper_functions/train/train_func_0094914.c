onCoreDatabaseServerChanged()
{

    if (d->_sqlModel) {
        disconnect(d->_sqlModel);
        delete d->_sqlModel;
    }

    d->_sqlModel = new QSqlTableModel(this, episodeBase()->database());
    d->_sqlModel->setTable(episodeBase()->table(Constants::Table_EPISODES));
    Utils::linkSignalsFromFirstModelToSecondModel(d->_sqlModel, this, false);
    connect(d->_sqlModel, SIGNAL(primeInsert(int,QSqlRecord&)), this, SLOT(populateNewRowWithDefault(int, QSqlRecord&)));
    d->updateFilter(patient()->uuid());
}
