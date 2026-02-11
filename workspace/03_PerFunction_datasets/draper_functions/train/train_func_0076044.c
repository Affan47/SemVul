DoClearTargetMenu()
{
    if (m_TargetMenu)
    {
        wxMenuItemList& items = m_TargetMenu->GetMenuItems();
        while (wxMenuItemList::Node* node = items.GetFirst())
        {
            if (node->GetData())
                m_TargetMenu->Delete(node->GetData());
        }


    }
}
