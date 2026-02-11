nifti_make_new_nim(const int dims[], int datatype, int data_fill)
{
   nifti_image    * nim;
   nifti_1_header * nhdr;

   nhdr = nifti_make_new_header(dims, datatype);
   if( !nhdr ) return NULL;

   nim = nifti_convert_nhdr2nim(*nhdr,NULL);
   free(nhdr);
   if( !nim ){
      fprintf(stderr,"** NMNN: nifti_convert_nhdr2nim failure\n");
      return NULL;
   }

   if( g_opts.debug > 1 )
      fprintf(stderr,"+d nifti_make_new_nim, data_fill = %d\n",data_fill);

   if( data_fill ) {
      nim->data = calloc(nim->nvox, nim->nbyper);


      if( !nim->data ) {
         fprintf(stderr,"** NMNN: failed to alloc %u bytes for data\n",
                 (unsigned)(nim->nvox*nim->nbyper));
         nifti_image_free(nim);
         nim = NULL;
      }
   }

   return nim;
}
