toogleToolbar(bool state)
{
    if (d->m_ToolBar) {
        d->m_ToolBar->setVisible(state);
        d->m_ToolBarIsVisible = state;
    }
}
