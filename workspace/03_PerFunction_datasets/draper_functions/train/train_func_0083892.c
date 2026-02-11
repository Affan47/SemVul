Draw( GRA_wxWidgets *graphicsOutput, wxDC &dc )
{
  xAxis_->Draw( graphicsOutput, dc );
  DrawXLabel( graphicsOutput, dc );
  yAxis_->Draw( graphicsOutput, dc );
  DrawYLabel( graphicsOutput, dc );
  if( boxXAxis_ )boxXAxis_->Draw( graphicsOutput, dc );
  if( boxYAxis_ )boxYAxis_->Draw( graphicsOutput, dc );


  GRA_setOfCharacteristics *xAxisC = xAxis_->GetCharacteristics();
  std::vector<double> ticX, ticY;
  xAxis_->GetTicCoordinates( ticX, ticY );
  std::size_t size = ticX.size();
  double const eps = 0.001;

  int lineTypeSave = graphicsOutput->GetLineType();
  graphicsOutput->SetLineType( gridLineType_ );
  wxPen wxpen( dc.GetPen() );
  wxpen.SetColour(
   ExGlobals::GetwxColor( static_cast<GRA_colorCharacteristic*>(xAxisC->Get(wxT("AXISCOLOR")))->Get()) );

  double xlaxis, ylaxis, xuaxis, yuaxis;
  xAxis_->GetOrigin( xlaxis, ylaxis );
  xAxis_->GetEndPoint( xuaxis, yuaxis );
  int ngrid = abs(xAxis_->GetGrid());
  for( std::size_t i=0; i<size; i+=ngrid )
  {
    double x = ticX[i];
    double y = ticY[i];
    if( fabs(x-xuaxis)>eps && fabs(x-xlaxis)>eps )
    {
      graphicsOutput->StartLine( x, y );
      graphicsOutput->ContinueLine( x, y+(yuaxis-ylaxis), dc );
    }
  }


  GRA_setOfCharacteristics *yAxisC = yAxis_->GetCharacteristics();
  yAxis_->GetTicCoordinates( ticX, ticY );
  size = ticX.size();

  wxpen.SetColour(
   ExGlobals::GetwxColor( static_cast<GRA_colorCharacteristic*>(yAxisC->Get(wxT("AXISCOLOR")))->Get()) );

  ngrid = abs(yAxis_->GetGrid());
  for( std::size_t i=0; i<size; i+=ngrid )
  {
    double x = ticX[i];
    double y = ticY[i];
    if( fabs(y-yuaxis)>eps && fabs(y-ylaxis)>eps )
    {
      graphicsOutput->StartLine( x, y );
      graphicsOutput->ContinueLine( x+(xuaxis-xlaxis), y, dc );
    }
  }
  graphicsOutput->SetLineType( lineTypeSave );
}
