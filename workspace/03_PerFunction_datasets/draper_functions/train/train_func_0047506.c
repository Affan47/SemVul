prtime()
{


  int units;
  units = 2;
  if(units==1)

     printf("%6.2f   ",mf_ticks2sec(Mf_currtime,division,tempo));
  else if (units==2)

     printf("%6.2f   ",(float) Mf_currtime/(float) division);
  else

    printf("%6ld  ",Mf_currtime);
  return 0;
}
