OnConnect( wxCommandEvent &WXUNUSED(event) )
{
  if( setup_ || !curve_ )return;
  int code = plotsymbolCodeSC_->GetValue();
  if( !connectCB_->IsChecked() )code *= -1;
  static_cast<GRA_intCharacteristic*>(curveChars_->Get(wxT("PLOTSYMBOL")))->Set( code );
  curve_->SetPlotsymbolCode( code );
  ReDraw();
}
