run( GameStates &gameState, bool onePlayerGame ) {
  activeChoice = 0;
  SetDifficulty::onePlayerGame = onePlayerGame;
  draw();
  while ( gameState == GS_SET_DIFFICULTY ) {
    handleEvents( gameState );
    draw();
    SDL_Delay( 50 );
  }
}
