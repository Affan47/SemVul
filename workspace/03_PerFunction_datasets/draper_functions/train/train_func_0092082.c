childrenChanged()
{

    if (m_documentElement)
        m_documentElement->deref();
    m_documentElement = 0;


    if (m_doctype)
        m_doctype->deref();
    m_doctype = 0;
}
