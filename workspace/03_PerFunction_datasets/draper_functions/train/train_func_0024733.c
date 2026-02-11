count_pieces(int player)

{
  int rv = 0;
  int i = 0, j = 0;

  for(i = 0; i < 8; i++) {
    for(j = 0; j < 8; j++) {
      if(pieces[i][j] == player)
	rv++;
    }
  }

  return(rv);
}
