AdjustFieldsSize()
{
    for (unsigned int i = 0 ; i < m_Elements.size(); i++)
    {
        wxWindow *ctrl = m_Elements[i].control;
        if (ctrl)
        {
            wxRect rect;
            GetFieldRectByPlugin(m_Elements[i].plugin, rect);
            ctrl->SetSize(rect.x + 2, rect.y + 2, rect.width - 4, rect.height - 4);
        }
    }
}
