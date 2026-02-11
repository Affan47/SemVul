setCurrentPage(int index)
{

    if (index == -1 || index >= d->m_stackedWidgets->count())
        d->m_stackedWidgets->setCurrentIndex(0);
    d->m_stackedWidgets->setCurrentIndex(index);
}
