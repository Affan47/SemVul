WidgetActivated( Widget *widget, Window *win ) {
  Point hex = mw->GetLastHex();
  Rect viewport;

  view->DisableUpdates();
  if ( !mv->HexVisible( hex ) ) mv->CenterOnHex( hex );
  Gam->SetCursor( hex );

  CalcViewPort( viewport );
  mw->SetViewPort( viewport );
  mw->Draw();
  view->EnableUpdates();
  view->Refresh();

  return GUI_OK;
}
