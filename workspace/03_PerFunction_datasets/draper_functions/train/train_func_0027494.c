AddMenuItem(uint8 Icon, int32 itemText, uint32 dtSender, uint32 dtAction, int32 boxText, uint32 BoxMoney, bool Coded)
{
    uint32 loc_idx = m_session->GetSessionDbLocaleIndex();

    char const* item_text = itemText ? sObjectMgr.GetMangosString(itemText, loc_idx) : "";
    char const* box_text = boxText ? sObjectMgr.GetMangosString(boxText, loc_idx) : "";

    AddMenuItem(Icon, std::string(item_text), dtSender, dtAction, std::string(box_text), BoxMoney, Coded);
}
