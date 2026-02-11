ParseGridPrimMiss (gridAttribType *attrib, double *grib_Data,
                               sInt4 Nx, sInt4 Ny, sInt4 *iain,
                               double unitM, double unitB, sInt4 *missCnt,
                               uChar f_wxType, sect2_WxType *WxType,
                               int startX, int startY, int subNx, int subNy)
{
   sInt4 x, y;
   double value;
   uChar f_maxmin = 0;
   uInt4 index;
   sInt4 *itemp = NULL;
   float *ftemp = NULL;


   for (y = 0; y < subNy; y++) {
      if (((startY + y - 1) < 0) || ((startY + y - 1) >= Ny)) {
         for (x = 0; x < subNx; x++) {
            *grib_Data++ = attrib->missPri;
            (*missCnt)++;
         }
      } else {
         if (attrib->fieldType) {
            itemp = iain + (startY + y - 1) * Nx + (startX - 1);
         } else {
            ftemp = ((float *) iain) + (startY + y - 1) * Nx + (startX - 1);
         }
         for (x = 0; x < subNx; x++) {
            if (((startX + x - 1) < 0) || ((startX + x - 1) >= Nx)) {
               *grib_Data++ = attrib->missPri;
               (*missCnt)++;
            } else {
               if (attrib->fieldType) {
                  value = (*itemp++);
               } else {
                  value = (*ftemp++);
               }


               if (value == attrib->missPri) {
                  (*missCnt)++;
               } else {

                  if (unitM == -10) {
                     value = pow (10.0, value);
                  } else {
                     value = unitM * value + unitB;
                  }
                  if (f_wxType) {
                     index = (uInt4) value;
                     if (index < WxType->dataLen) {
                        if (WxType->ugly[index].f_valid) {
                           WxType->ugly[index].f_valid = 2;
                        } else {


                           value = attrib->missPri;
                           (*missCnt)++;
                        }
                     }
                  }
                  if ((!f_wxType) || (value != attrib->missPri)) {
                     if (f_maxmin) {
                        if (value < attrib->min) {
                           attrib->min = value;
                        } else if (value > attrib->max) {
                           attrib->max = value;
                        }
                     } else {
                        attrib->min = attrib->max = value;
                        f_maxmin = 1;
                     }
                  }
               }
               *grib_Data++ = value;
            }
         }
      }
   }
   attrib->f_maxmin = f_maxmin;
}
