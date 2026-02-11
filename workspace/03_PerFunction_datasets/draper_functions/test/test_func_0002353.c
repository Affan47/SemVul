DoSetSize(int x, int y, int width, int height, int sizeFlags)
{
    wxSize curSize( GetSize() );
    wxSize bestSize( DoGetBestSize() );

    if (width == -1)
        width = curSize.GetWidth();
    if (width < 10)
        width = bestSize.GetWidth();

    if (height == -1)
        height = curSize.GetHeight();
    if (height < 5)
        height = bestSize.GetHeight();

    wxWindow::DoSetSize(x, y, width, height, sizeFlags);

    if (m_labelButton)
        m_labelButton->SetSize(0, 0, width - wxMENUBUTTON_DROP_WIDTH, height);
    if (m_dropdownButton)
        m_dropdownButton->SetSize(width-wxMENUBUTTON_DROP_WIDTH, 0, wxMENUBUTTON_DROP_WIDTH, height);
}
