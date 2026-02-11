glEnd ()
{
  if (n == 0) return;

  glEnableClientState (GL_VERTEX_ARRAY);

  if (pref != VERTEXARRAY_V3C4T2 && pref != VERTEXARRAY_V3C4)
    glEnableClientState (GL_NORMAL_ARRAY);
  else
    glDisableClientState (GL_NORMAL_ARRAY);

	if (pref != VERTEXARRAY_V3N3T2)
    glEnableClientState (GL_COLOR_ARRAY);
  else
    glDisableClientState (GL_COLOR_ARRAY);

	if (pref != VERTEXARRAY_V3N3C4 && pref != VERTEXARRAY_V3C4)
    glEnableClientState (GL_TEXTURE_COORD_ARRAY);
  else
    glDisableClientState (GL_TEXTURE_COORD_ARRAY);

  glVertexPointer (3,	GL_FLOAT,	sizeof (float) * stride, &data [0]);
  glNormalPointer (GL_FLOAT, sizeof (float) * stride, &data [3]);
  glColorPointer (4, GL_FLOAT, sizeof (float) * stride, &data [6]);
  glTexCoordPointer (2, GL_FLOAT, sizeof (float) * stride, &data [10]);

  glDrawArrays (type, 0, n);
}
