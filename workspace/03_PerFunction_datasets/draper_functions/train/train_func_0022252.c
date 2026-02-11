read_red1(bgav_input_context_t * ctx,
                     red1_t * ret)
  {


  if(!bgav_input_read_32_be(ctx, &ret->unknown1) ||
     !bgav_input_read_32_be(ctx, &ret->pts_timescale) ||
     !bgav_input_read_32_be(ctx, &ret->unknown2) ||
     !bgav_input_read_32_be(ctx, &ret->unknown3) ||
     !bgav_input_read_32_be(ctx, &ret->unknown4) ||
     !bgav_input_read_32_be(ctx, &ret->unknown5) ||
     !bgav_input_read_32_be(ctx, &ret->unknown6) ||
     !bgav_input_read_32_be(ctx, &ret->unknown7) ||
     !bgav_input_read_32_be(ctx, &ret->unknown8) ||
     !bgav_input_read_32_be(ctx, &ret->unknown9) ||
     !bgav_input_read_32_be(ctx, &ret->unknown10) ||
     !bgav_input_read_32_be(ctx, &ret->width) ||
     !bgav_input_read_32_be(ctx, &ret->height) ||
     !bgav_input_read_32_be(ctx, &ret->video_timescale) ||
     !bgav_input_read_16_be(ctx, &ret->frame_duration) ||
     !bgav_input_read_8(ctx, &ret->unknown15)
     )
    return 0;

  if(bgav_input_read_data(ctx, (uint8_t*)(ret->name), 257) < 257)
    return 0;
  return 1;
  }
