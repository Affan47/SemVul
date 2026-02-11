WebPRescalerInit(WebPRescaler* const wrk, int src_width, int src_height,
                      uint8_t* const dst, int dst_width, int dst_height,
                      int dst_stride, int num_channels, int x_add, int x_sub,
                      int y_add, int y_sub, int32_t* const work) {
  wrk->x_expand = (src_width < dst_width);
  wrk->src_width = src_width;
  wrk->src_height = src_height;
  wrk->dst_width = dst_width;
  wrk->dst_height = dst_height;
  wrk->dst = dst;
  wrk->dst_stride = dst_stride;
  wrk->num_channels = num_channels;

  wrk->x_add = wrk->x_expand ? (x_sub - 1) : x_add - x_sub;
  wrk->x_sub = wrk->x_expand ? (x_add - 1) : x_sub;
  wrk->y_accum = y_add;
  wrk->y_add = y_add;
  wrk->y_sub = y_sub;
  wrk->fx_scale = (1 << RFIX) / x_sub;
  wrk->fy_scale = (1 << RFIX) / y_sub;
  wrk->fxy_scale = wrk->x_expand ?
      ((int64_t)dst_height << RFIX) / (x_sub * src_height) :
      ((int64_t)dst_height << RFIX) / (x_add * src_height);
  wrk->irow = work;
  wrk->frow = work + num_channels * dst_width;
}
