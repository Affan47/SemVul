SetDashes( int number_of_dashes, const wxDash *dash )
{
    wxCHECK_RET(Ok(), wxT("Invalid generic pen"));
    wxCHECK_RET(((number_of_dashes == 0) && !dash) ||
                ((number_of_dashes >  0) &&  dash), wxT("Invalid dashes for pen"));


    if (M_GPENDATA->m_dash)
    {
        free(M_GPENDATA->m_dash);
        M_GPENDATA->m_dash = NULL;
        M_GPENDATA->m_dash_count = 0;
    }

    if (!dash)
        return;

    M_GPENDATA->m_dash_count = number_of_dashes;
    M_GPENDATA->m_dash = (wxDash*)malloc(number_of_dashes*sizeof(wxDash));
    memcpy(M_GPENDATA->m_dash, dash, number_of_dashes*sizeof(wxDash));
}
