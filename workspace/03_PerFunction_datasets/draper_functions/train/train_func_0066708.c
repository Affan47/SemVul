kml2pen (
    LineStylePtr poKmlLineStyle,
    OGRStylePen *poOgrStylePen)
{

    if (!poOgrStylePen)
        poOgrStylePen = new OGRStylePen (  );


    poOgrStylePen->SetUnit(OGRSTUPixel);


    if ( poKmlLineStyle->has_width (  ) )
        poOgrStylePen->SetWidth ( poKmlLineStyle->get_width (  ) );


    if ( poKmlLineStyle->has_color (  ) ) {
        Color32 poKmlColor = poKmlLineStyle->get_color (  );
        char szColor[10] = { };
        snprintf ( szColor, sizeof ( szColor ), "#%02X%02X%02X%02X",
                   poKmlColor.get_red (  ),
                   poKmlColor.get_green (  ),
                   poKmlColor.get_blue (  ), poKmlColor.get_alpha (  ) );
        poOgrStylePen->SetColor ( szColor );
    }

    return poOgrStylePen;
}
