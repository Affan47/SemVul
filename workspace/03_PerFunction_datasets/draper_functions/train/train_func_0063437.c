removedFromDocument()
{
    HTMLElementImpl::removedFromDocument();

    if (m_styleSheet)
        document()->updateStyleSelector();
}
