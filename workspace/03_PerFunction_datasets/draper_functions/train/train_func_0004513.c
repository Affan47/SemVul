vmballoon_page_size(bool is_2m_page)
{
	if (is_2m_page)
		return 1 << VMW_BALLOON_2M_SHIFT;

	return 1;
}
