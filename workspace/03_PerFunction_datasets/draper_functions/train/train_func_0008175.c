_dxfgetdelta(method_type method,float min, float max, float *incr)
{
   int n=100,sub=0;
   float delta=0,lo=0,fuzz;
   char fmt[20];
   float range,start=0;

   switch(method){
    case(PERCENT_ROUND):
      if (*incr>0){
         range = max-min;
         fuzz = *incr * .1;
         n = (int)(1.0/ (*incr-fuzz));
         _dxfaxes_delta(&start,&range,1,&n,&lo,&delta,fmt,&sub,0,0);
         *incr=delta;
      }
      else
         *incr=0;
      break;
    case(PERCENT):
      delta = *incr *(max-min);
      *incr = delta;
      break;
    default:
      break;
   }

   return OK;
}
