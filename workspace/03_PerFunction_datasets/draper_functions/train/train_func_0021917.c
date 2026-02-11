whose_territory(const struct influence_data *q, int pos)
{
  float bi = q->black_influence[pos];
  float wi = q->white_influence[pos];
  float terr = q->territory_value[pos];

  ASSERT_ON_BOARD1(pos);

  if (bi > 0.0 && wi == 0.0 && terr < -territory_determination_value)
     return BLACK;
  if (wi > 0.0 && bi == 0.0 && terr > territory_determination_value)
     return WHITE;

  return EMPTY;
}
