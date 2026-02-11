decf_v_v(float *v1, float *v2, int num)
{
   int i;

   for (i=0; i<num; i++)
      v1[i] -= v2[i];
   return(v1);
}
