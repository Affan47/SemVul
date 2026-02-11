setProperty(int id, int value, bool important )
{
    if(!m_lstValues) {
	m_lstValues = new QList<CSSProperty*>;
    }
    removeProperty(id);

    CSSValueImpl * cssValue = new CSSPrimitiveValueImpl(value);
    setParsedValue(id, cssValue, important, m_lstValues);
    setChanged();
}
