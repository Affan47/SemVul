AbortDigitizing()
{


  startStopB_->SetLabel( wxT("Start digitizing") );
  std::vector<double>().swap( xd_ );
  std::vector<double>().swap( yd_ );
}
