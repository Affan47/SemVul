GetProgressRect() {
    if (m_ProgressBar->IsShown()) {
        return &m_ProgressRect;
    } else {
        return NULL;
    }
}
