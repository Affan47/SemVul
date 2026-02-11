SetXAxisLabel(const wxString &label)
{
    if (label.IsEmpty())
        m_xLabel = wxT("X - Axis");
    else
        m_xLabel = label;

    wxFont font = GetAxisLabelFont();
    GetTextExtent(m_xLabel, &m_xLabelRect.width, &m_xLabelRect.height, NULL, NULL, &font);

    m_xLabel = label;
    Refresh();
    DoSize();
}
