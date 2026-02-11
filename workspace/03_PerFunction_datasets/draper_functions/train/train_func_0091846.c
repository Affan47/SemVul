item(int index) const
{
    return (index >= 0 && index < count()) ? m_data[index] : QString();
}
