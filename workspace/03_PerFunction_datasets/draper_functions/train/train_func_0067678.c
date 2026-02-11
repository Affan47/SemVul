InitRGBRescaler(const VP8Io* const io, WebPDecParams* const p) {
  const int has_alpha = WebPIsAlphaMode(p->output->colorspace);
  const int out_width  = io->scaled_width;
  const int out_height = io->scaled_height;
  const int uv_in_width  = (io->mb_w + 1) >> 1;
  const int uv_in_height = (io->mb_h + 1) >> 1;
  const size_t work_size = 2 * out_width;
  int32_t* work;
  uint8_t* tmp;
  size_t tmp_size1, tmp_size2, total_size;

  tmp_size1 = 3 * work_size;
  tmp_size2 = 3 * out_width;
  if (has_alpha) {
    tmp_size1 += work_size;
    tmp_size2 += out_width;
  }
  total_size = tmp_size1 * sizeof(*work) + tmp_size2 * sizeof(*tmp);
  p->memory = WebPSafeCalloc(1ULL, total_size);
  if (p->memory == NULL) {
    return 0;
  }
  work = (int32_t*)p->memory;
  tmp = (uint8_t*)(work + tmp_size1);
  WebPRescalerInit(&p->scaler_y, io->mb_w, io->mb_h,
                   tmp + 0 * out_width, out_width, out_height, 0, 1,
                   io->mb_w, out_width, io->mb_h, out_height,
                   work + 0 * work_size);
  WebPRescalerInit(&p->scaler_u, uv_in_width, uv_in_height,
                   tmp + 1 * out_width, out_width, out_height, 0, 1,
                   io->mb_w, 2 * out_width, io->mb_h, 2 * out_height,
                   work + 1 * work_size);
  WebPRescalerInit(&p->scaler_v, uv_in_width, uv_in_height,
                   tmp + 2 * out_width, out_width, out_height, 0, 1,
                   io->mb_w, 2 * out_width, io->mb_h, 2 * out_height,
                   work + 2 * work_size);
  p->emit = EmitRescaledRGB;

  if (has_alpha) {
    WebPRescalerInit(&p->scaler_a, io->mb_w, io->mb_h,
                     tmp + 3 * out_width, out_width, out_height, 0, 1,
                     io->mb_w, out_width, io->mb_h, out_height,
                     work + 3 * work_size);
    p->emit_alpha = EmitRescaledAlphaRGB;
    if (p->output->colorspace == MODE_RGBA_4444 ||
        p->output->colorspace == MODE_rgbA_4444) {
      p->emit_alpha_row = ExportAlphaRGBA4444;
    } else {
      p->emit_alpha_row = ExportAlpha;
    }
  }
  return 1;
}
