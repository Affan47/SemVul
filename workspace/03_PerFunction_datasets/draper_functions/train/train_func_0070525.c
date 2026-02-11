fullest_directions (const FttCellFace * face,
				FttDirection d[FTT_DIMENSION])
{
  FttComponent c = face->d/2, i;
  FttCell * mixed = GFS_IS_MIXED (face->cell) ? face->cell : face->neighbor;
  GfsSolidVector * s = GFS_STATE (mixed)->solid;

  d[0] = face->d;
  for (i = 1; i < FTT_DIMENSION; i++) {
    guint cp = (c + i) % FTT_DIMENSION;
    d[i] = s->s[2*cp] > s->s[2*cp + 1] ? 2*cp : 2*cp + 1;
  }
}
