IsSameAs(const wxGenericBrush& brush) const
{
    wxCHECK_MSG(Ok() && brush.Ok(), 1, wxT("Invalid generic brush"));
    wxGenericBrushRefData *bData = (wxGenericBrushRefData*)brush.GetRefData();
#if wxCHECK_VERSION(2,7,0)

    return (M_GBRUSHDATA->m_colour  == bData->m_colour) &&
           (M_GBRUSHDATA->m_style   == bData->m_style);
#else
    return (M_GBRUSHDATA->m_colour  == bData->m_colour) &&
           (M_GBRUSHDATA->m_style   == bData->m_style) &&
           (M_GBRUSHDATA->m_stipple == bData->m_stipple);
#endif
}
