quietResetFocus()
{
    assert(m_focusNode != this);
    if (m_focusNode) {
        if (m_focusNode->active())
            setActiveNode(0);

        m_focusNode->setFocus(false);
        m_focusNode->deref();
    }
    m_focusNode = 0;


    if (view())
        view()->setFocus();
}
