slotFilterListByEcoPlayer(QString tag, QString eco, QString player)
{
    m_model->filter()->setAll(1);
    TagSearch ts(m_model->filter()->database(),  tag, player);
    TagSearch ts3(m_model->filter()->database(), TagNameECO,   eco);
    m_model->filter()->executeSearch(ts);
    m_model->filter()->executeSearch(ts3, Search::And);
    updateFilter();
    emit raiseRequest();
    emit searchDone();
}
