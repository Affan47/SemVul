SetColorTable( GDALColorTable *poTableIn )

{
    if( poColorTable != NULL )
    {
        delete poColorTable;
        poColorTable = NULL;
    }

    if( poTableIn )
    {
        poColorTable = poTableIn->Clone();
        eColorInterp = GCI_PaletteIndex;
    }

    ((VRTDataset *)poDS)->SetNeedsFlush();

    return CE_None;
}
