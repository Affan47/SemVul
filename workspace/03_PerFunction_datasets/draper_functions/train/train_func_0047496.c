Create(wxWindow* parent, wxWindowID id,
                            const wxString& label, const wxBitmap &bitmap,
                            const wxPoint& pos, const wxSize& size,
                            long style, const wxValidator& val,
                            const wxString& name)
{
    if (!wxControl::Create(parent,id,pos,size,wxNO_BORDER|wxCLIP_CHILDREN,val,name))
        return false;

    wxControl::SetLabel(label);
    wxControl::SetBackgroundColour(parent->GetBackgroundColour());
    wxControl::SetForegroundColour(parent->GetForegroundColour());
    wxControl::SetFont(parent->GetFont());

    if (bitmap.Ok()) m_bmpLabel = bitmap;

    if (!SetButtonStyle(style)) return false;

    wxSize bestSize = DoGetBestSize();
    SetSize(wxSize(size.x<0 ? bestSize.x:size.x, size.y<0 ? bestSize.y:size.y));
#if wxCHECK_VERSION(2,7,0)
    SetInitialSize(GetSize());
#else
    SetBestSize(GetSize());
#endif

    CalcLayout(true);
    return true;
}
