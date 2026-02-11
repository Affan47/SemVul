gap_layer_copy_content (gint32 dst_drawable_id, gint32 src_drawable_id)
{
  GimpPixelRgn srcPR, dstPR;
  GimpDrawable *src_drawable;
  GimpDrawable *dst_drawable;
  gpointer  pr;

  src_drawable = gimp_drawable_get (src_drawable_id);
  dst_drawable = gimp_drawable_get (dst_drawable_id);

  if((src_drawable->width  != dst_drawable->width)
  || (src_drawable->height != dst_drawable->height)
  || (src_drawable->bpp    != dst_drawable->bpp))
  {
    printf("gap_layer_copy_content: calling ERROR src_drawable and dst_drawable do not match in size or bpp\n");
    printf("src: w:%d h:%d bpp:%d\n"
           ,(int)src_drawable->width
           ,(int)src_drawable->height
           ,(int)src_drawable->bpp
           );
    printf("dst: w:%d h:%d bpp:%d\n"
           ,(int)dst_drawable->width
           ,(int)dst_drawable->height
           ,(int)dst_drawable->bpp
           );
    gimp_drawable_detach(src_drawable);
    gimp_drawable_detach(dst_drawable);
    return FALSE;
  }

  gimp_pixel_rgn_init (&srcPR, src_drawable, 0, 0
                      , src_drawable->width, src_drawable->height
                      , FALSE
                      , FALSE
                       );
  gimp_pixel_rgn_init (&dstPR, dst_drawable, 0, 0
                      , dst_drawable->width, dst_drawable->height
                      , TRUE
                      , FALSE
                       );


  for (pr = gimp_pixel_rgns_register (2, &srcPR, &dstPR);
       pr != NULL;
       pr = gimp_pixel_rgns_process (pr))
  {
      p_copy_rgn_render_region (&srcPR, &dstPR);
  }

  gimp_drawable_flush (dst_drawable);
  gimp_drawable_detach(src_drawable);
  gimp_drawable_detach(dst_drawable);
  return TRUE;
}
