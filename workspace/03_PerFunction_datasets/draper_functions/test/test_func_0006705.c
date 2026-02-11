search_contour(const int x_search, const int y_search,
                   const int search_len,
                   const int x_loc, const int y_loc,
                   const int x_edge, const int y_edge,
                   const int scan_clock,
                   unsigned char *bdata, const int iw, const int ih)
{
   int cur_x_loc, cur_y_loc;
   int cur_x_edge, cur_y_edge;
   int next_x_loc, next_y_loc;
   int next_x_edge, next_y_edge;
   int i;


   cur_x_loc = x_loc;
   cur_y_loc = y_loc;
   cur_x_edge = x_edge;
   cur_y_edge = y_edge;


   for(i = 0; i < search_len; i++){

      if(next_contour_pixel(&next_x_loc, &next_y_loc,
                            &next_x_edge, &next_y_edge,
                            cur_x_loc, cur_y_loc,
                            cur_x_edge, cur_y_edge,
                            scan_clock, bdata, iw, ih)){


         if((next_x_loc == x_search) && (next_y_loc == y_search)){

            return(FOUND);
         }


         cur_x_loc = next_x_loc;
         cur_y_loc = next_y_loc;
         cur_x_edge = next_x_edge;
         cur_y_edge = next_y_edge;
      }

      else{

         return(NOT_FOUND);
      }
   }


   return(NOT_FOUND);
}
