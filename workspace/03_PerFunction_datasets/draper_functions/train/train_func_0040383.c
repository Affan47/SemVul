GetColorInterpretation()

{
    SRPDataset* poDS = (SRPDataset*)this->poDS;

    if( poDS->oCT.GetColorEntryCount() > 0 )
        return GCI_PaletteIndex;
    else
        return GCI_GrayIndex;
}
