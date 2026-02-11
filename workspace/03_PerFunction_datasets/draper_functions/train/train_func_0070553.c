start_scan_nbr(const int x_prev, const int y_prev,
                   const int x_next, const int y_next)
{
   if((x_prev==x_next) && (y_next > y_prev))
      return(SOUTH);
   else if ((x_prev==x_next) && (y_next < y_prev))
      return(NORTH);
   else if ((x_next > x_prev) && (y_prev==y_next))
      return(EAST);
   else if ((x_next < x_prev) && (y_prev==y_next))
      return(WEST);


   return(INVALID_DIR);
}
