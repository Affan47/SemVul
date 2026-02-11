check_parameters_of_create_bmp_for_rect_in_rect(void)
{
   if( (Er1<1.0) || (Er2 <1.0))
      exit_with_msg_and_exit_code((char *) "Both Er1  and Er2 must be >= 1.0",100);
   if(aa+dd>WW)
      exit_with_msg_and_exit_code((char *) "the dielectric extends horizontally outside the box (a+d>W)",100);
   if(bb+ww>=WW)
      exit_with_msg_and_exit_code((char *) "the inner conductor extends horizontally beyond the outer conductor(b+w>=W)",101);
   if(cc<=0.0)
      exit_with_msg_and_exit_code((char *) "The inner conductors's thickness (c) must be greater than zero ",12);
   if(hh<=0.0)
      exit_with_msg_and_exit_code((char *) "The thickness of dielectric Er2 (h) must be greater than zero ",12);
   if(hh+cc>=HH)
      exit_with_msg_and_exit_code((char *) "the inner conductor extends verticaly beyond the outer conductor(c+h>=H)",101);
   if((WW<=0.0) || (HH<=0.0) || (aa<0.0) || (bb<0.0) || (cc<=0.0) || (dd<=0.0)
   ||(ww<=0.0) || (hh<=0.0))
      exit_with_msg_and_exit_code((char *) "W,H,c,d,w, & h must be positive numbers. Non-integers are okay, but they must be >0 \n",102);

}
