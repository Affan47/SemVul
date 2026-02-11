StartLine( double x, double y, double &xw, double &yw )
{


  double xmin = static_cast<GRA_doubleCharacteristic*>(xAxisCharacteristics_->Get(wxT("MIN")))->Get();
  double xmax = static_cast<GRA_doubleCharacteristic*>(xAxisCharacteristics_->Get(wxT("MAX")))->Get();
  double ymin = static_cast<GRA_doubleCharacteristic*>(yAxisCharacteristics_->Get(wxT("MIN")))->Get();
  double ymax = static_cast<GRA_doubleCharacteristic*>(yAxisCharacteristics_->Get(wxT("MAX")))->Get();
  bool clip = static_cast<GRA_boolCharacteristic*>(dataCurveCharacteristics_->Get(wxT("CLIP")))->Get();

  if( !clip || ((x-xmin)*(xmax-x)>=0.0 && (y-ymin)*(ymax-y)>=0.0) )GraphToWorld(x,y,xw,yw);
  xPrevious_ = x;
  yPrevious_ = y;
}
