slotFilterListByPlayer(QString s)
{
    m_model->filter()->setAll(1);
    TagSearch ts(m_model->filter()->database(),  TagNameWhite, s);
    TagSearch ts2(m_model->filter()->database(), TagNameBlack, s);
    m_model->filter()->executeSearch(ts);
    m_model->filter()->executeSearch(ts2, Search::Or);
    updateFilter();
    emit raiseRequest();
    emit searchDone();
}
