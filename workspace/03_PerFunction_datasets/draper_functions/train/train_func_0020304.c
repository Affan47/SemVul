putimage ( int x1, int y1, void* img )
{
   char* src = (char*) img;

   if ( agmp->windowstatus == 100 ) {
      char* buf = (char*) (agmp->scanlinelength * y1 + x1 * agmp->byteperpix + agmp->linearaddress);

      trleheader*   hd = (trleheader*) img;

      if ( hd->id == 16973 ) {

         collategraphicoperations cgo ( x1, y1, x1+hd->x, y1+hd->y );

         int spacelength = agmp->scanlinelength - hd->x - 1;

         src  += sizeof ( *hd );

         int x = 0;
         for ( int c = 0; c < hd->size; c++ ) {
            if ( *src == hd->rle ) {
               x += src[1];
               for ( int i = src[1]; i > 0; i-- )
                  *(buf++) = src[2];

               src += 3;
               c+=2;

            } else {
               *(buf++) = *(src++);
               x++;
            }

            if ( x > hd->x ) {
               buf += spacelength;
               x = 0;
            }
         }
      } else {
         Uint16* w = (Uint16*) img;
         collategraphicoperations cgo ( x1, y1, x1+w[0], y1+w[1] );
         int spacelength = agmp->scanlinelength - *w - 1;
         src += 4;
         for ( int y = w[1] + 1; y > 0; y-- ) {
            for ( int x = w[0]+1; x > 0; x-- )
               *(buf++) = *(src++);

            buf+=spacelength;
         }
      }
   }

}
