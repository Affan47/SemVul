find3_incloc(int32 ifi, int32 call_ifi)
{
 struct incloc_t *ilp, *ilp2;

 if ((ilp2 = find_incloc(ifi)) == NULL) return(NULL);


 for (;;)
  {
   ifi = ilp2->incfrom_fnind;
   if (ifi == call_ifi) return(ilp2);
   ilp = ilp2;
   if ((ilp2 = find_incloc(ifi)) == NULL) break;
  }
 return(ilp);
}
