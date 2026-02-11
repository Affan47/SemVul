setIsRedirected( bool b )
{
    m_redirected = b;
    if (!b && m_rw && m_rw->widget()) {
        setInPaintEventFlag( m_rw->widget(), false );
        m_rw->widget()->setAttribute(Qt::WA_OpaquePaintEvent, false);
        m_rw->widget()->removeEventFilter(m_rw->view());
    }
}
