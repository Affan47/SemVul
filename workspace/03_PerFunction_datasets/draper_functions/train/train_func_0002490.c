SelectCols( int colLeft, int colRight, bool addToSelected, bool sendEvt )
{
    if (HasSelectionMode(wxSHEET_SelectRows) || (colLeft > colRight))
        return false;


    return SelectBlock( wxSheetBlock(0, colLeft, GetNumberRows()+1, colRight-colLeft+1),
                        addToSelected, sendEvt );
}
