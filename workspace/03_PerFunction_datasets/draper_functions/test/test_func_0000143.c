RemoveCategory(uint8 cat)
{
	if (m_category == cat) {

		m_category = 0;
	} else if (m_category > cat) {

		m_category--;
	}
}
