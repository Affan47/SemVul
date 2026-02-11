SetStipple(const wxBitmap& stipple)
{
    wxCHECK_RET(Ok(), wxT("Invalid generic brush"));
    M_GBRUSHDATA->m_stipple = stipple;
    M_GBRUSHDATA->m_style = stipple.GetMask() ? wxSTIPPLE_MASK_OPAQUE : wxSTIPPLE;

}
