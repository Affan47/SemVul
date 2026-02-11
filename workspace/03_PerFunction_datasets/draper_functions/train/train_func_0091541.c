flam3_copy_xform(flam3_xform *dest, flam3_xform *src) {

   int j;


   if (dest->num_motion>0)
      flam3_delete_motion_elements(dest);


   *dest = *src;


   dest->num_motion=0;
   dest->motion=NULL;

   if (src->num_motion>0) {
      for (j=0;j<src->num_motion;j++)
         flam3_add_motion_element(dest);

      memcpy(dest->motion,src->motion,src->num_motion*sizeof(flam3_xform));
   }
}
