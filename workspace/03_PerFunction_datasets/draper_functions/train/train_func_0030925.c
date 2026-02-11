_embryo_fp_abs(Embryo_Program *ep __UNUSED__, Embryo_Cell *params)
{

   float f;

   if (params[0] != (1 * sizeof(Embryo_Cell))) return 0;
   f = EMBRYO_CELL_TO_FLOAT(params[1]);
   f = (f >= 0) ? f : -f;
   return EMBRYO_FLOAT_TO_CELL(f);
}
