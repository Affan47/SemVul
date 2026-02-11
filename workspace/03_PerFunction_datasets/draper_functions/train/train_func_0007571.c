EmitFancyRGB(const VP8Io* const io, WebPDecParams* const p) {
  int num_lines_out = io->mb_h;
  const WebPRGBABuffer* const buf = &p->output->u.RGBA;
  uint8_t* dst = buf->rgba + io->mb_y * buf->stride;
  WebPUpsampleLinePairFunc upsample = WebPUpsamplers[p->output->colorspace];
  const uint8_t* cur_y = io->y;
  const uint8_t* cur_u = io->u;
  const uint8_t* cur_v = io->v;
  const uint8_t* top_u = p->tmp_u;
  const uint8_t* top_v = p->tmp_v;
  int y = io->mb_y;
  const int y_end = io->mb_y + io->mb_h;
  const int mb_w = io->mb_w;
  const int uv_w = (mb_w + 1) / 2;

  if (y == 0) {

    upsample(cur_y, NULL, cur_u, cur_v, cur_u, cur_v, dst, NULL, mb_w);
  } else {

    upsample(p->tmp_y, cur_y, top_u, top_v, cur_u, cur_v,
             dst - buf->stride, dst, mb_w);
    ++num_lines_out;
  }

  for (; y + 2 < y_end; y += 2) {
    top_u = cur_u;
    top_v = cur_v;
    cur_u += io->uv_stride;
    cur_v += io->uv_stride;
    dst += 2 * buf->stride;
    cur_y += 2 * io->y_stride;
    upsample(cur_y - io->y_stride, cur_y,
             top_u, top_v, cur_u, cur_v,
             dst - buf->stride, dst, mb_w);
  }

  cur_y += io->y_stride;
  if (io->crop_top + y_end < io->crop_bottom) {

    memcpy(p->tmp_y, cur_y, mb_w * sizeof(*p->tmp_y));
    memcpy(p->tmp_u, cur_u, uv_w * sizeof(*p->tmp_u));
    memcpy(p->tmp_v, cur_v, uv_w * sizeof(*p->tmp_v));


    num_lines_out--;
  } else {

    if (!(y_end & 1)) {
      upsample(cur_y, NULL, cur_u, cur_v, cur_u, cur_v,
               dst + buf->stride, NULL, mb_w);
    }
  }
  return num_lines_out;
}
