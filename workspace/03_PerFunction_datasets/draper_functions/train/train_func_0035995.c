PlaneCount()
{
 unsigned int count=0;

     for (int i = 0; i < MAXCOLORPLANES; i++)
     {
         count += NumRows[i] * ColorDepth[i];
     }

  return count;
}
