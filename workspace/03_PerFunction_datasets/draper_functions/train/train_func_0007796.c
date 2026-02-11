nifti_type_and_names_match( nifti_image * nim, int show_warn )
{
   char func[] = "nifti_type_and_names_match";
   const char * ext_h;
   const char * ext_i;
   int  errs = 0;


   if( !nim ){
      if( show_warn ) fprintf(stderr,"** %s: missing nifti_image\n", func);
      return -1;
   }
   if( !nim->fname ){
      if( show_warn ) fprintf(stderr,"** %s: missing header filename\n", func);
      errs++;
   }
   if( !nim->iname ){
      if( show_warn ) fprintf(stderr,"** %s: missing image filename\n", func);
      errs++;
   }
   if( !is_valid_nifti_type(nim->nifti_type) ){
      if( show_warn )
         fprintf(stderr,"** %s: bad nifti_type %d\n", func, nim->nifti_type);
      errs++;
   }

   if( errs ) return -1;


   ext_h = nifti_find_file_extension( nim->fname );
   ext_i = nifti_find_file_extension( nim->iname );


   if( !ext_h ){
      if( show_warn )
         fprintf(stderr,"-d missing NIFTI extension in header filename, %s\n",
                 nim->fname);
      errs++;
   }
   if( !ext_i ){
      if( show_warn )
         fprintf(stderr,"-d missing NIFTI extension in image filename, %s\n",
                 nim->iname);
      errs++;
   }

   if( errs ) return 0;


   if( nim->nifti_type == NIFTI_FTYPE_NIFTI1_1 ){
      if( fileext_n_compare(ext_h,".nii",4) ) {
         if( show_warn )
            fprintf(stderr,
            "-d NIFTI_FTYPE 1, but no .nii extension in header filename, %s\n",
            nim->fname);
         errs++;
      }
      if( fileext_n_compare(ext_i,".nii",4) ) {
         if( show_warn )
            fprintf(stderr,
            "-d NIFTI_FTYPE 1, but no .nii extension in image filename, %s\n",
            nim->iname);
         errs++;
      }
      if( strcmp(nim->fname, nim->iname) != 0 ){
         if( show_warn )
            fprintf(stderr,
            "-d NIFTI_FTYPE 1, but header and image filenames differ: %s, %s\n",
            nim->fname, nim->iname);
         errs++;
      }
   }
   else if( (nim->nifti_type == NIFTI_FTYPE_NIFTI1_2) ||
            (nim->nifti_type == NIFTI_FTYPE_ANALYZE) )
   {
      if( fileext_n_compare(ext_h,".hdr",4) != 0 ){
         if( show_warn )
            fprintf(stderr,"-d no '.hdr' extension, but NIFTI type is %d, %s\n",
                    nim->nifti_type, nim->fname);
         errs++;
      }
      if( fileext_n_compare(ext_i,".img",4) != 0 ){
         if( show_warn )
            fprintf(stderr,"-d no '.img' extension, but NIFTI type is %d, %s\n",
                    nim->nifti_type, nim->iname);
         errs++;
      }
   }


   return 1;
}
