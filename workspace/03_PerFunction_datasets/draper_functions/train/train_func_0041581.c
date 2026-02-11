xsh_frame_qual_update(cpl_frame *frame, const cpl_frame *bpmap,xsh_instrument* inst)
{
   xsh_pre* pre=NULL;
   const char* frame_name=NULL;
   const char* bpmap_name=NULL;
   const char* frame_tag=NULL;

   cpl_image* map_self=NULL;
   cpl_image* map_right=NULL;
   cpl_frame* product=NULL;
   const int mode_or=1;
   assure(frame != NULL, CPL_ERROR_NULL_INPUT,"INPUT frame is NULL pointer" ) ;
   assure(bpmap != NULL, CPL_ERROR_NULL_INPUT,"BP MAP frame is NULL pointer" ) ;

   check(frame_name=cpl_frame_get_filename(frame));
   check(frame_tag=cpl_frame_get_tag(frame));
   check(bpmap_name=cpl_frame_get_filename(bpmap));

   check(pre=xsh_pre_load(frame,inst));
   check(map_right=cpl_image_load(bpmap_name,CPL_TYPE_INT,0,0));
   xsh_badpixelmap_image_coadd(&(pre->qual), map_right,mode_or);
   check(product=xsh_pre_save(pre,frame_name,frame_tag,0));

  cleanup:
   xsh_pre_free(&pre);
   xsh_free_image(&map_self);
   xsh_free_image(&map_right);
   xsh_free_frame(&product);
   return cpl_error_get_code();

}
