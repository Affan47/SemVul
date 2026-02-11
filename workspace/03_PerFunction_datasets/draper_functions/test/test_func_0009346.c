endContainer(int &exceptioncode) const
{
    if (m_detached) {
        exceptioncode = DOMException::INVALID_STATE_ERR;
        return 0;
    }

    return m_endContainer;
}
