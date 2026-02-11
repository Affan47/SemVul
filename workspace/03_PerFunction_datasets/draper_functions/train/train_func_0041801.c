SetSaveTitlePosition( int val )
{


  for( int i = 0 ; i < NUMBER_OF_ALIGNED_AXIS ; ++ i )
    {
    this->XAxes[i]->SetSaveTitlePosition( val );
    this->YAxes[i]->SetSaveTitlePosition( val );
    }
}
