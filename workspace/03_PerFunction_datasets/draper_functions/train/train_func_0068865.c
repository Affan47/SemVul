setVisible(const int position, const bool visible)
{
	int i = indexOf(position);

	if (i!=NO_INDEX) {
		if(dynamic_cast<KBBGraphicsItem*>(m_items[i]))
			(dynamic_cast<KBBGraphicsItem*>(m_items[i]))->setVisible(visible);
	}
}
