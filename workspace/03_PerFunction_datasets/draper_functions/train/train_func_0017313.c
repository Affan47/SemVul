redraw()
{
  int s, v;

  for (s=0; s<4; s++)
    for (v=0; v<13; v++)
      put_picture(cards[s][v], M+v*CARD_FAN_RIGHT, M+s*(M+H), 0, 0, W, H);

  for (s=0; s<4; s++)
    for (v=0; v<13; v++)
      put_picture(cards[s][v], 300+s*(W+M), M+v*CARD_FAN_DOWN, 0, 0, W, H);

  for (s=0; s<4; s++)
    put_picture(cards[s][0], 300+s*(W+M), M+3*(M+H), 0, 0, W, H);
}
