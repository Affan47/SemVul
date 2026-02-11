MouseUp( const SDL_MouseButtonEvent &button ) {
  if ( Clicked() && (button.button == SDL_BUTTON_LEFT) ) {
    Release();
    mousehit = false;
  }
  return GUI_OK;
}
