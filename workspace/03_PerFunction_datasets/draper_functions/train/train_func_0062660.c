ShiftRows( unsigned  char state[4][4] )
{
  int i,j;
  unsigned char tmp[4][4];

  for(i=0; i<4; i++){
    for(j=0; j<4; j++)
      tmp[i][j] = state[i][(j+i)%4];
  }
  memcpy( state, tmp, 4*4 );
}
