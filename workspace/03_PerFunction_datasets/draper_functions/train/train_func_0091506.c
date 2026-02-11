align_bitmap_image(int W,int H,unsigned char *unaligned_image,unsigned char *byte_aligned_image)
{
   int i, j, vector_aligned=0, vector_original=0;

   for(j=0;j<H;j++)
   {
      for(i=0;i <W; ++i)
      {


	 if( (i==0) && (vector_aligned%4!=0) )
	    vector_aligned++;
	 if( (i==0) && (vector_aligned%4!=0) )
	    vector_aligned++;
	 if( (i==0) && (vector_aligned%4!=0) )
	    vector_aligned++;
	 byte_aligned_image[vector_aligned]=unaligned_image[vector_original];
	 byte_aligned_image[vector_aligned+1]=unaligned_image[vector_original+1];
	 byte_aligned_image[vector_aligned+2]=unaligned_image[vector_original+2];
         vector_original+=3;
         vector_aligned+=3;
      }
   }
   if( vector_aligned%4!=0 )
      vector_aligned++;
   if( vector_aligned%4!=0 )
      vector_aligned++;
   if( vector_aligned%4!=0 )
      vector_aligned++;
   return(vector_aligned);
}
