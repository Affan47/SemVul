operator==(const QContactDetail& other) const
{
    if (! (d.constData()->m_definitionName == other.d.constData()->m_definitionName))
        return false;

    if (d.constData()->m_access != other.d.constData()->m_access)
        return false;

    if (d.constData()->m_values != other.d.constData()->m_values)
        return false;

    return true;
}
