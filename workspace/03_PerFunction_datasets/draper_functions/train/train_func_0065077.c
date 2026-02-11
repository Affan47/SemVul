AddTree()
{
   UseUpId();
   if( mShuttleMode != eIsCreating )
      return wxDynamicCast(wxWindow::FindWindowById( miId, mpDlg), wxTreeCtrl);
   wxTreeCtrl * pTreeCtrl;
   SetProportions( 1 );
   mpWind = pTreeCtrl = new wxTreeCtrl(mpParent, miId, wxDefaultPosition, wxDefaultSize,
      Style( wxTR_HAS_BUTTONS ));
   pTreeCtrl->SetMinSize( wxSize( 120,650 ));
   UpdateSizers();
   return pTreeCtrl;
}
