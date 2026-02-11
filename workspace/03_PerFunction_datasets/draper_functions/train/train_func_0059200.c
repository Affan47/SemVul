rubber_grab()
{
  float dx[2];
  float d;
  float min_d=0;
  int min_i=0;
  int i;

  for (i = 0; i < m_grid_sizeX*m_grid_sizeY; i++)
    {
      dx[0] = m_mass[i].x[0] - ctrX;
      dx[1] = m_mass[i].x[1] - ctrY;
      d = sqrt(dx[0]*dx[0] + dx[1]*dx[1]);
      if (i == 0 || d < min_d)
        {
          min_i = i;
          min_d = d;
        }
    }

  return min_i;
}
