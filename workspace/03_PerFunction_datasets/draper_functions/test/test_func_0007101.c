setPage(int page)
{
    Q_FOREACH(DocumentObserver *obs, m_observers) {
        obs->pageChanged(page);
    }

    m_currentPage = page;
}
