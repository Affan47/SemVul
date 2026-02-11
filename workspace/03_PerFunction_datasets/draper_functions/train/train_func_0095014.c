FractalMountain(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3],
                     int pegged[3])
{
  GLfloat lengths[MAXLEVEL];
  GLfloat fraction[8] = { 0.3, 0.3, 0.4, 0.2, 0.3, 0.2, 0.4, 0.4  };
  GLfloat bias[8]     = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1  };
  int i;
  float avglen = (xzlength(v1, v2) +
                  xzlength(v2, v3) +
		  xzlength(v3, v1) / 3);

  for (i = 0; i < 3; i++) {
    Verts[0][i] = v1[i];
    Verts[1][i] = v2[i];
    Verts[2][i] = v3[i];
    Pegged[i] = pegged[i];
  }

  Slopes[0] = xzslope(Verts[0], Verts[1]);
  Slopes[1] = xzslope(Verts[1], Verts[2]);
  Slopes[2] = xzslope(Verts[2], Verts[0]);

  lengths[0] = avglen;
  for (i = 1; i < Level; i++) {
    lengths[i] = lengths[i-1]/2;
  }

  for (i = 0; i < Level; i++) {
    DispFactor[i] = (lengths[i] * ((i <= 7) ? fraction[i] : fraction[7]));
    DispBias[i]   = ((i <= 7) ? bias[i] : bias[7]);
  }

  glBegin(GL_TRIANGLES);
    FMR(v1, v2, v3, 0);
  glEnd();
}
