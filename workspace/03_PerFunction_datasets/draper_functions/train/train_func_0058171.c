RealFFTf(fft_type *buffer,HFFT h)
{
   fft_type *A,*B;
   fft_type *sptr;
   fft_type *endptr1,*endptr2;
   int *br1,*br2;
   fft_type HRplus,HRminus,HIplus,HIminus;
   fft_type v1,v2,sin,cos;

   int ButterfliesPerGroup=h->Points/2;


   endptr1=buffer+h->Points*2;

   while(ButterfliesPerGroup>0)
   {
      A=buffer;
      B=buffer+ButterfliesPerGroup*2;
      sptr=h->SinTable;

      while(A<endptr1)
      {
         sin=*sptr;
         cos=*(sptr+1);
         endptr2=B;
         while(A<endptr2)
         {
            v1=*B*cos + *(B+1)*sin;
            v2=*B*sin - *(B+1)*cos;
            *B=(*A+v1);
            *(A++)=*(B++)-2*v1;
            *B=(*A-v2);
            *(A++)=*(B++)+2*v2;
         }
         A=B;
         B+=ButterfliesPerGroup*2;
         sptr+=2;
      }
      ButterfliesPerGroup >>= 1;
   }

   br1=h->BitReversed+1;
   br2=h->BitReversed+h->Points-1;

   while(br1<br2)
   {
      sin=h->SinTable[*br1];
      cos=h->SinTable[*br1+1];
      A=buffer+*br1;
      B=buffer+*br2;
      HRplus = (HRminus = *A     - *B    ) + (*B     * 2);
      HIplus = (HIminus = *(A+1) - *(B+1)) + (*(B+1) * 2);
      v1 = (sin*HRminus - cos*HIplus);
      v2 = (cos*HRminus + sin*HIplus);
      *A = (HRplus  + v1) * (fft_type)0.5;
      *B = *A - v1;
      *(A+1) = (HIminus + v2) * (fft_type)0.5;
      *(B+1) = *(A+1) - HIminus;

      br1++;
      br2--;
   }

   A=buffer+*br1+1;
   *A=-*A;


   v1=buffer[0]-buffer[1];
   buffer[0]+=buffer[1];
   buffer[1]=v1;
}
