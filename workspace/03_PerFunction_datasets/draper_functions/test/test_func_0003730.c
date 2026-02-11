AdjustSlotRefsForPreAnys(int critPrependedAnys)
{
	GdlRuleItem::AdjustSlotRefsForPreAnys(critPrependedAnys);

	for (size_t i = 0; i < m_vpavs.size(); i++)
		m_vpavs[i]->AdjustSlotRefsForPreAnys(critPrependedAnys, this);
}
