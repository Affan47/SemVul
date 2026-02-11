Create( const wxBitmap &stipple )
{
    UnRef();
    wxCHECK_RET(stipple.Ok(), wxT("Invalid bitmap in wxGenericBrush::Create"));

    int style = stipple.GetMask() ? wxSTIPPLE_MASK_OPAQUE : wxSTIPPLE;
    m_refData = new wxGenericBrushRefData(wxNullGenericColour, style);
    M_GBRUSHDATA->m_stipple = stipple;
}
