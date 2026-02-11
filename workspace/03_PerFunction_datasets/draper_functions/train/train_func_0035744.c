glNormal3f (float x, float y, float z)
{
  if (n >= max) reallocData ();
  data [stride * n + 3] = x;
  data [stride * n + 4] = y;
  data [stride * n + 5] = z;
}
