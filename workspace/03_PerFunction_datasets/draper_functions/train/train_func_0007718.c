setViewExpanded(bool expand)
{
    if (expand) {
        QList<int> sizes;
        sizes << 0 << this->width();
        m_ui->splitter->setSizes(sizes);
    } else {
        if (isViewExpanded()) {
            QList<int> sizes;
            sizes << 1 << 3;
            m_ui->splitter->setSizes(sizes);
        }
    }
}
