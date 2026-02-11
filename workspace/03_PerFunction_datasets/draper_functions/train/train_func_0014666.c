_embryo_fp_atan2(Embryo_Program *ep __UNUSED__, Embryo_Cell *params)
{


   float f, ff;

   if (params[0] != (3 * sizeof(Embryo_Cell))) return 0;
   f = EMBRYO_CELL_TO_FLOAT(params[1]);
   ff = EMBRYO_CELL_TO_FLOAT(params[2]);
   f = atan2f(f, ff);
   f = _embryo_fp_degrees_to_radians(f, params[3]);
   return EMBRYO_FLOAT_TO_CELL(f);
}
