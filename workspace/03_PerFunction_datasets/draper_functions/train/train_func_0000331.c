progressBar(QWidget *w)
{
    if (!d->m_ProgressBar)
        d->m_ProgressBar = new QProgressBar(w);
    return d->m_ProgressBar;
}
