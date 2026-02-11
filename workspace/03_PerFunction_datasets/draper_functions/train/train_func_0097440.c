VideoModeChange( void ) {
  if ( (view->Width() != w) || (view->Height() != h) ) {
    SetSize( view->Width(), view->Height() );

    mview->Resize( *this );
    Draw();
  }
}
