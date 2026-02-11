VectorSubset(const Vector &other, int start, int len)
{
   Vector v(len);
   int i;
   for(i=0; i<len; i++)
      v[i] = other[start+i];
   return v;
}
