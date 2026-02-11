bgav_mpeg4_vol_header_dump(bgav_mpeg4_vol_header_t * h)
  {
  bgav_dprintf("VOL header\n");

  bgav_dprintf("  random_accessible_vol:              %d\n",
               h->random_accessible_vol);
  bgav_dprintf("  video_object_type_indication:       %d\n",
               h->video_object_type_indication);
  bgav_dprintf("  is_object_layer_identifier:         %d\n",
               h->is_object_layer_identifier);
  if (h->is_object_layer_identifier)
    {
    bgav_dprintf("  video_object_layer_verid:           %d\n", h->video_object_layer_verid);
    bgav_dprintf("  video_object_layer_priority:        %d\n", h->video_object_layer_priority);
    }
  bgav_dprintf("  aspect_ratio_info:                  %d\n", h->aspect_ratio_info);
  if(h->aspect_ratio_info == 15) {
  bgav_dprintf("  par_width:                          %d\n", h->par_width);
  bgav_dprintf("  par_height:                         %d\n", h->par_height);
  }
  bgav_dprintf("  vol_control_parameters:             %d\n", h->vol_control_parameters);

  if (h->vol_control_parameters)
    {
    bgav_dprintf("  chroma_format:                      %d\n", h->chroma_format);
    bgav_dprintf("  low_delay:                          %d\n", h->low_delay);
    bgav_dprintf("  vbv_parameters:                     %d\n", h->vbv_parameters);
    if (h->vbv_parameters)
      {
      bgav_dprintf("  first_half_bit_rate:                %d\n", h->first_half_bit_rate);
      bgav_dprintf("  latter_half_bit_rate:               %d\n", h->latter_half_bit_rate);
      bgav_dprintf("  first_half_vbv_buffer_size:         %d\n", h->first_half_vbv_buffer_size);
      bgav_dprintf("  latter_half_vbv_buffer_size:        %d\n", h->latter_half_vbv_buffer_size);
      bgav_dprintf("  first_half_vbv_occupancy:           %d\n", h->first_half_vbv_occupancy);
      bgav_dprintf("  latter_half_vbv_occupancy:          %d\n", h->latter_half_vbv_occupancy);
      }
    }
  bgav_dprintf("  video_object_layer_shape:           %d\n", h->video_object_layer_shape);
  if ((h->video_object_layer_shape == 3) &&
      (h->video_object_layer_verid != 1)) {
  bgav_dprintf("  video_object_layer_shape_extension: %d\n", h->video_object_layer_shape_extension);
  }
  bgav_dprintf("  vop_time_increment_resolution:      %d\n", h->vop_time_increment_resolution);
  bgav_dprintf("  fixed_vop_rate:                     %d\n", h->fixed_vop_rate);
  if (h->fixed_vop_rate) {
  bgav_dprintf("  fixed_vop_time_increment:           %d\n", h->fixed_vop_time_increment);
  }

  }
