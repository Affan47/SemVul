bgav_h264_sps_dump(bgav_h264_sps_t * sps)
  {
  int i;
  bgav_dprintf("SPS:\n");
  bgav_dprintf("  profile_idc:                             %d\n", sps->profile_idc);
  bgav_dprintf("  constraint_set0_flag:                    %d\n", sps->constraint_set0_flag);
  bgav_dprintf("  constraint_set1_flag:                    %d\n", sps->constraint_set1_flag);
  bgav_dprintf("  constraint_set2_flag:                    %d\n", sps->constraint_set2_flag);
  bgav_dprintf("  constraint_set3_flag:                    %d\n", sps->constraint_set3_flag);
  bgav_dprintf("  level_idc:                               %d\n", sps->level_idc);
  bgav_dprintf("  seq_parameter_set_id:                    %d\n", sps->seq_parameter_set_id);

  if(sps->profile_idc == 100 ||
     sps->profile_idc == 110 ||
     sps->profile_idc == 122 ||
     sps->profile_idc == 244 ||
     sps->profile_idc == 44 ||
     sps->profile_idc == 83 ||
     sps->profile_idc == 86 )
    {
    bgav_dprintf("  chroma_format_idc:                       %d\n", sps->chroma_format_idc);
    if(sps->chroma_format_idc == 3)
      bgav_dprintf("  separate_colour_plane_flag:              %d\n", sps->separate_colour_plane_flag);

    bgav_dprintf("  bit_depth_luma_minus8:                   %d\n", sps->bit_depth_luma_minus8);
    bgav_dprintf("  bit_depth_chroma_minus8:                 %d\n", sps->bit_depth_chroma_minus8);
    bgav_dprintf("  qpprime_y_zero_transform_bypass_flag:    %d\n", sps->qpprime_y_zero_transform_bypass_flag);
    bgav_dprintf("  seq_scaling_matrix_present_flag:         %d\n", sps->seq_scaling_matrix_present_flag);
    }

  bgav_dprintf("  log2_max_frame_num_minus4:               %d\n", sps->log2_max_frame_num_minus4);
  bgav_dprintf("  pic_order_cnt_type:                      %d\n", sps->pic_order_cnt_type);

  if( sps->pic_order_cnt_type == 0 )
    bgav_dprintf("  log2_max_pic_order_cnt_lsb_minus4:       %d\n", sps->log2_max_pic_order_cnt_lsb_minus4);
  else if(sps->pic_order_cnt_type == 1)
    {
    bgav_dprintf("  delta_pic_order_always_zero_flag:      %d\n", sps->delta_pic_order_always_zero_flag);
    bgav_dprintf("  offset_for_non_ref_pic:                %d\n", sps->offset_for_non_ref_pic);
    bgav_dprintf("  offset_for_top_to_bottom_field:        %d\n", sps->offset_for_top_to_bottom_field);
    bgav_dprintf("  num_ref_frames_in_pic_order_cnt_cycle: %d\n", sps->num_ref_frames_in_pic_order_cnt_cycle);

    for(i = 0; i < sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
      {
      bgav_dprintf("  offset_for_ref_frame[%d]:              %d\n", i, sps->offset_for_ref_frame[i]);
      }
    }

  bgav_dprintf("  num_ref_frames:                          %d\n", sps->num_ref_frames);
  bgav_dprintf("  gaps_in_frame_num_value_allowed_flag:    %d\n", sps->gaps_in_frame_num_value_allowed_flag);
  bgav_dprintf("  pic_width_in_mbs_minus1:                 %d\n", sps->pic_width_in_mbs_minus1);
  bgav_dprintf("  pic_height_in_map_units_minus1:          %d\n", sps->pic_height_in_map_units_minus1);
  bgav_dprintf("  frame_mbs_only_flag:                     %d\n", sps->frame_mbs_only_flag);

  if( !sps->frame_mbs_only_flag )
    bgav_dprintf("  mb_adaptive_frame_field_flag:            %d\n", sps->mb_adaptive_frame_field_flag);
  bgav_dprintf("  direct_8x8_inference_flag:               %d\n", sps->direct_8x8_inference_flag);
  bgav_dprintf("  frame_cropping_flag:                     %d\n", sps->frame_cropping_flag);
  if( sps->frame_cropping_flag )
    {
    bgav_dprintf("  frame_crop_left_offset:                  %d\n", sps->frame_crop_left_offset);
    bgav_dprintf("  frame_crop_right_offset:                 %d\n", sps->frame_crop_right_offset);
    bgav_dprintf("  frame_crop_top_offset:                   %d\n", sps->frame_crop_top_offset);
    bgav_dprintf("  frame_crop_bottom_offset:                %d\n", sps->frame_crop_bottom_offset);
    }
  bgav_dprintf("  vui_parameters_present_flag:             %d\n", sps->vui_parameters_present_flag);

  if(sps->vui_parameters_present_flag)
    vui_dump(&sps->vui);

  }
