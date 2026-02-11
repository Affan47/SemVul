zoomChanged( int zoom )
{
   if ( !changeActive )
      if ( zoomSlider )
         zoomSlider->SetPosition( 100 - zoom );
}
