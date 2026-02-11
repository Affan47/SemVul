UpdateWatch()
{
    m_watch->MarkAsChangedRecursive(false);
    ::UpdateWatch(m_grid, GetRealRoot(m_grid), m_watch, true);
    m_grid->Refresh();
    Fit();
}
