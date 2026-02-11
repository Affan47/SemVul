getShpEarth (double majEarth, double minEarth, sInt4 * shapeEarth,
                         sInt4 * factRad, sInt4 * valRad, sInt4 * factMaj,
                         sInt4 * valMaj, sInt4 * factMin, sInt4 * valMin)
{
   *factRad = 0;
   *factMaj = 0;
   *factMin = 0;
   *valRad = 0;
   *valMaj = 0;
   *valMin = 0;
   if (majEarth == minEarth) {
      if (majEarth == 6367.47) {
         *shapeEarth = 0;
         *valRad = 6367470;
      } else if (majEarth == 6371.229) {
         *shapeEarth = 6;
         *valRad = 6371229;
      } else {
         *shapeEarth = 1;
         *valRad = NearestInt (majEarth * 1000);
      }
   } else {
      if ((majEarth == 6378.16) && (minEarth == 6356.775)) {
         *shapeEarth = 2;
         *valMaj = 6378160;
         *valMin = 6356775;
      } else if ((majEarth == 6378.137) && (minEarth == 6356.752314)) {
         *shapeEarth = 4;
         *valMaj = 6378137;

         *factMin = 2;

         *valMin = 635675231;
      } else {
         *shapeEarth = 7;
         *valMaj = NearestInt (majEarth * 1000);
         *valMin = NearestInt (majEarth * 1000);
      }
   }
}
