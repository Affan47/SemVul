setRowUpper( int elementIndex, double elementValue )
{
#ifndef NDEBUG
     int n = numberRows_;
     if (elementIndex < 0 || elementIndex >= n) {
          indexError(elementIndex, "setRowUpper");
     }
#endif
     if (elementValue > 1.0e27)
          elementValue = COIN_DBL_MAX;
     if (rowUpper_[elementIndex] != elementValue) {
          rowUpper_[elementIndex] = elementValue;
          if ((whatsChanged_ & 1) != 0) {

               whatsChanged_ &= ~32;
               if (rowUpper_[elementIndex] == COIN_DBL_MAX) {
                    rowUpperWork_[elementIndex] = COIN_DBL_MAX;
               } else if (!rowScale_) {
                    rowUpperWork_[elementIndex] = elementValue * rhsScale_;
               } else {
                    rowUpperWork_[elementIndex] = elementValue * rhsScale_
                                                  * rowScale_[elementIndex];
               }
          }
     }
}
