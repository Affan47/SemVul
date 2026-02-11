clear()
{
    m_OriginalValue = m_FormItem->valueReferences()->defaultValue().toString();
    setDate(m_OriginalValue);
}
