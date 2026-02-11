registerType(const Kolf::ItemMetadata& metadata, ItemCreator creator)
{
	m_entries << Entry(metadata, creator);
}
