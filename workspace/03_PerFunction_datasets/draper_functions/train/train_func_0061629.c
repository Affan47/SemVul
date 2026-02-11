glk_image_get_info(glui32 image, glui32 *width, glui32 *height) {
  giblorb_err_t err;
  giblorb_result_t res;

  err = giblorb_load_resource(giblorb_get_resource_map(), giblorb_method_Memory, &res, giblorb_ID_Pict, image);

  if (err) {
    printf("DEBUG: Couldn't get pict id %d from blorb, err = %d\n", image, err);
    return FALSE;
  }

  if (res.chunktype == 0x504e4720) {


    *width  = ntohl(*(glui32*)((char*)res.data.ptr+16));
    *height = ntohl(*(glui32*)((char*)res.data.ptr+20));

    printf("DEBUG: found image size of %d x %d\n", *width, *height);

    return TRUE;
  } else {
    printf("Don't know how to handle chunktype=0x%x in image_get_info\n", res.chunktype);
    exit(30);
  }
}
