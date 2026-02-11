cbf_compute_reciprocal_cell (double cell[6], double rcell[6]){

   double volume, degtorad, radtodeg;
   #define acos_deg(x) (atan2(sqrt(1.-(x)*(x)),(x))*radtodeg)

   cbf_compute_cell_volume (cell, &volume);

   degtorad = atan2(1.,1.)/45.;
   radtodeg = 1./degtorad;

   if (volume <= 0. ) return CBF_ARGUMENT;

   rcell[0] = cell[1]*cell[2]*sin(cell[3]*degtorad)/volume;

   rcell[1] = cell[2]*cell[0]*sin(cell[4]*degtorad)/volume;

   rcell[2] = cell[0]*cell[1]*sin(cell[5]*degtorad)/volume;

   rcell[3] = acos_deg((cos(cell[4]*degtorad)*cos(cell[5]*degtorad) - cos(cell[3]*degtorad))/(sin(cell[4]*degtorad)*sin(cell[5]*degtorad)));

   rcell[4] = acos_deg((cos(cell[5]*degtorad)*cos(cell[3]*degtorad) - cos(cell[4]*degtorad))/(sin(cell[5]*degtorad)*sin(cell[3]*degtorad)));

   rcell[5] = acos_deg((cos(cell[3]*degtorad)*cos(cell[4]*degtorad) - cos(cell[5]*degtorad))/(sin(cell[3]*degtorad)*sin(cell[4]*degtorad)));

   return 0;

}
