documentAdded(Document* document)
{
	m_deltas.insert(document, new Deltas(document));
}
