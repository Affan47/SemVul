SearchAndGetInt( int Wert, int* Arr, int* Res )
         {
            int Anz = Arr[0];
            int Pos = 1;
            while ( Anz> 0 ) {
              if (( Wert & Arr[Pos]) == Arr[Pos+1] ) {
                 *Res = Arr[Pos+2];
                 return  Anz > 0;
              }
              Pos += 3;
              Anz--;
            }
            return  Anz> 0;
         }
