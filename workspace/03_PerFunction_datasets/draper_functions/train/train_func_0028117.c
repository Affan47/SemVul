value() const
{
    if (!m_root)
    {
        throw CRuntimeException("Root has not been set");
    }
    return m_root->value();
}
