xsh_util_frameset_collapse_mean(cpl_frameset* set,
                           xsh_instrument* instrument)
{
   cpl_frame* result=NULL;
   cpl_frame* frm=NULL;

   cpl_image* ima=NULL;
   cpl_image* err=NULL;

   cpl_image* ima_sum=NULL;
   cpl_image* err_sum=NULL;
   cpl_image* qua_sum=NULL;
   cpl_propertylist* hdat=NULL;
   cpl_propertylist* herr=NULL;
   cpl_propertylist* hqua=NULL;
   char* name=NULL;
   char* tag=NULL;
   const char* fname=NULL;
   int size=0;
   int i=0;


   size=cpl_frameset_get_size(set);
   for(i=0;i<size;i++) {

      frm=cpl_frameset_get_frame(set,i);
      fname=cpl_frame_get_filename(frm);

      ima=cpl_image_load(fname,XSH_PRE_DATA_TYPE,0,0);
      err=cpl_image_load(fname,XSH_PRE_ERRS_TYPE,0,1);

      cpl_image_multiply(err,err);
      if(i==0) {
         ima_sum=cpl_image_duplicate(ima);
         err_sum=cpl_image_duplicate(err);
      } else {
         cpl_image_add(ima_sum,ima);
         cpl_image_add(err_sum,err);
      }

      xsh_free_image(&ima);
      xsh_free_image(&err);

   }


   cpl_image_divide_scalar(ima_sum,size);
   cpl_image_divide_scalar(err_sum,size);


   check(cpl_image_power(err_sum,0.5));


   qua_sum=cpl_image_load(fname,XSH_PRE_QUAL_TYPE,0,2);

   frm=cpl_frameset_get_frame(set,0);
   fname=cpl_frame_get_filename(frm);
   hdat=cpl_propertylist_load(fname,0);
   herr=cpl_propertylist_load(fname,1);
   hqua=cpl_propertylist_load(fname,2);

   name=cpl_sprintf("SKY_AVG_%s.fits",xsh_instrument_arm_tostring( instrument));
   tag=cpl_sprintf("SKY_AVG_%s",xsh_instrument_arm_tostring( instrument));

   check(cpl_image_save(ima_sum,name,XSH_PRE_DATA_BPP,hdat,CPL_IO_DEFAULT));
   check(cpl_image_save(err_sum,name,XSH_PRE_ERRS_BPP,herr,CPL_IO_EXTEND));
   check(cpl_image_save(qua_sum,name,XSH_PRE_QUAL_BPP,hqua,CPL_IO_EXTEND));
   result=xsh_frame_product(name,tag,CPL_FRAME_TYPE_IMAGE,
                            CPL_FRAME_GROUP_PRODUCT,CPL_FRAME_LEVEL_FINAL);
   xsh_add_temporary_file(name);

 cleanup:

   xsh_free_image(&ima);
   xsh_free_image(&err);

   xsh_free_image(&ima_sum);
   xsh_free_image(&err_sum);
   xsh_free_image(&qua_sum);

   xsh_free_propertylist(&hdat);
   xsh_free_propertylist(&herr);
   xsh_free_propertylist(&hqua);

   cpl_free(name);
   cpl_free(tag);

   return result;
}
