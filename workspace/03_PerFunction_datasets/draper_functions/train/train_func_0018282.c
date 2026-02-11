nifti_read_next_extension( nifti1_extension * nex, nifti_image *nim,
                                      int remain, znzFile fp )
{
   int swap = nim->byteorder != nifti_short_order();
   int count, size, code;


   nex->esize = nex->ecode = 0;
   nex->edata = NULL;

   if( remain < 16 ){
      if( g_opts.debug > 2 )
         fprintf(stderr,"-d only %d bytes remain, so no extension\n", remain);
      return 0;
   }


   count = (int)znzread( &size, 4, 1, fp );
   if( count == 1 ) count += (int)znzread( &code, 4, 1, fp );

   if( count != 2 ){
      if( g_opts.debug > 2 )
         fprintf(stderr,"-d current extension read failed\n");
      znzseek(fp, -4*count, SEEK_CUR);
      return 0;
   }

   if( swap ){
      if( g_opts.debug > 2 )
         fprintf(stderr,"-d pre-swap exts: code %d, size %d\n", code, size);

      nifti_swap_4bytes(1, &size);
      nifti_swap_4bytes(1, &code);
   }

   if( g_opts.debug > 2 )
      fprintf(stderr,"-d potential extension: code %d, size %d\n", code, size);

   if( !nifti_check_extension(nim, size, code, remain) ){
      if( znzseek(fp, -8, SEEK_CUR) < 0 ){
         fprintf(stderr,"** failure to back out of extension read!\n");
         return -1;
      }
      return 0;
   }


   nex->esize = size;
   nex->ecode = code;

   size -= 8;
   nex->edata = (char *)malloc(size * sizeof(char));
   if( !nex->edata ){
      fprintf(stderr,"** failed to allocate %d bytes for extension\n",size);
      return -1;
   }

   count = (int)znzread(nex->edata, 1, size, fp);
   if( count < size ){
      if( g_opts.debug > 0 )
         fprintf(stderr,"-d read only %d (of %d) bytes for extension\n",
                 count, size);
      free(nex->edata);
      nex->edata = NULL;
      return -1;
   }


   if( g_opts.debug > 2 )
      fprintf(stderr,"+d successfully read extension, code %d, size %d\n",
              nex->ecode, nex->esize);

   return nex->esize;
}
