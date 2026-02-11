setRefreshSearchResultMethod(RefreshSearchResult method)
{
    disconnect(d->ui->searchLine, SIGNAL(textChanged(QString)), this, SLOT(refreshFilter()));
    disconnect(d->ui->searchLine, SIGNAL(textEdited(QString)), this, SLOT(refreshFilter()));
    d->m_refreshMethod = method;
    if (method == WhileTyping)
        connect(d->ui->searchLine, SIGNAL(textChanged(QString)), this, SLOT(refreshFilter()));
    else
        connect(d->ui->searchLine, SIGNAL(returnPressed()), this, SLOT(refreshFilter()));
}
