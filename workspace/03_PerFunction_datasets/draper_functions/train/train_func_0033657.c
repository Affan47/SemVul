cog_virt_frame_render_resample_vert_1tap (CogFrame * frame, void *_dest,
    int component, int i)
{
  uint8_t *dest = _dest;
  uint8_t *src1;
  int n_src;
  int scale = frame->param1;
  int acc;
  int src_i;

  acc = scale * i;
  src_i = acc >> 8;


  n_src = frame->virt_frame1->components[component].height;
  src1 = cog_virt_frame_get_line (frame->virt_frame1, component,
      CLAMP (src_i + 0, 0, n_src - 1));

  orc_memcpy (dest, src1, frame->components[component].width);
}
