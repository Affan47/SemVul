SetPropertyBackgroundColour( wxPGPropArg id,
                                                  const wxColour& colour,
                                                  int flags )
{
    wxPG_PROP_ARG_CALL_PROLOG()

    size_t i;
    int colInd = -1;

    long colAsLong = wxPG_COLOUR(colour.Red(),colour.Green(),colour.Blue());


    for ( i=(m_arrBgBrushes.GetCount()-1); i>0; i-- )
    {
        if ( ((wxPGBrush*)m_arrBgBrushes.Item(i))->GetColourAsLong() ==
                colAsLong )
        {
            colInd = i;
            break;
        }
    }

    if ( colInd < 0 )
    {
        colInd = m_arrBgBrushes.GetCount();
        wxCHECK_RET( colInd < 256,
                     wxT("wxPropertyGrid: Warning - Only 255 different ")
                     wxT("property background colours allowed.") );
        m_arrBgBrushes.Add( (void*)new wxPGBrush(colour) );
    }


    SetBackgroundColourIndex(p, colInd, flags);


    DrawItemAndChildren(p);
}
