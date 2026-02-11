Set( unsigned char red, unsigned char green,
                           unsigned char blue, unsigned char alpha )
{
    wxCHECK_RET(Ok(), wxT("Invalid generic colour"));
    M_GCOLOURDATA->m_r = red;
    M_GCOLOURDATA->m_g = green;
    M_GCOLOURDATA->m_b = blue;
    M_GCOLOURDATA->m_a = alpha;
}
