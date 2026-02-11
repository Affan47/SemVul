drawRank (float xp, float yp, float zp, int rank, float zoom)
{
  rank --;
  if (rank < 0) return;
  float x = xp / 10.0, y = yp / 10.0, z = zp;
  float tx1 = 0.5 * (rank % 2);
  float tx2 = tx1 + 0.5;
  float ty1 = 0.755 - 0.25 * (rank / 2);
  float ty2 = ty1 + 0.24;
  zoom /= 10;
  gl->enableTextures (texranks->textureID);
  if (antialiasing) gl->enableLinearTexture (texranks->textureID);
  else gl->disableLinearTexture (texranks->textureID);
  gl->enableAlphaBlending ();
  glEnable (GL_ALPHA_TEST);
  glAlphaFunc (GL_GEQUAL, 0.35);


  glBegin (GL_QUADS);
  glColor4ub (255, 255, 255, 200);
  glTexCoord2f (tx1, ty1);
  glVertex3f (x, y, z);
  glTexCoord2f (tx2, ty1);
  glVertex3f (x + zoom * 2, y, z);
  glTexCoord2f (tx2, ty2);
  glVertex3f (x + zoom * 2, y + zoom, z);
  glTexCoord2f (tx1, ty2);
  glVertex3f (x, y + zoom, z);
  glEnd ();

  glDisable (GL_ALPHA_TEST);
  gl->disableAlphaBlending ();
  glDisable (GL_TEXTURE_2D);
}
