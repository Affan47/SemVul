sinfo_new_convert_ZEROs_to_0_for_cubes_range(cpl_imagelist * cube,
                                             const int z_min,const int z_max)
{
    int i ;
    cpl_image* i_img=NULL;

    if ( cube == NULL )
    {
        sinfo_msg_error("no input cube given!") ;
        return ;
    }
    for ( i = z_min ; i < z_max ; i++ )
    {
      i_img=cpl_imagelist_get(cube,i);
      sinfo_new_convert_ZEROs_to_0_for_images(i_img) ;
      cpl_imagelist_set(cube,i_img,i);
    }
    return ;
}
