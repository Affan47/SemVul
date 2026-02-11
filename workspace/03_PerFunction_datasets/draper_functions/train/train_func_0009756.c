StartMultiColumn(int nCols, int PositionFlags)
{
   if( mShuttleMode != eIsCreating )
      return;
   mpSubSizer = new wxFlexGridSizer( nCols );
   UpdateSizersCore( false, PositionFlags | wxALL );
}
