GetColorInterpretation()

{
    if( poCT != NULL )
        return GCI_PaletteIndex;
    else if( nOGDIImageType == 1 && eFamily == Image && nComponent == 0 )
        return GCI_RedBand;
    else if( nOGDIImageType == 1 && eFamily == Image && nComponent == 1 )
        return GCI_GreenBand;
    else if( nOGDIImageType == 1 && eFamily == Image && nComponent == 2 )
        return GCI_BlueBand;
    else if( nOGDIImageType == 1 && eFamily == Image && nComponent == 3 )
        return GCI_AlphaBand;
    else
        return GCI_Undefined;
}
