setVariant(const QString& variant)
{
	if (!Chess::BoardFactory::variants().contains(variant))
		return false;

	m_variant = variant;
	return true;
}
