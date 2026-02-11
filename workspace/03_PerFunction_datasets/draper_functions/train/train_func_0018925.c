VFilter(SmoothParams* const p) {
  const uint8_t* src = p->src_;
  const int w = p->width_;
  uint16_t* const cur = p->cur_;
  const uint16_t* const top = p->top_;
  uint16_t* const out = p->end_;
  uint16_t sum = 0;
  int x;

  for (x = 0; x < w; ++x) {
    uint16_t new_value;
    sum += src[x];
    new_value = top[x] + sum;
    out[x] = new_value - cur[x];
    cur[x] = new_value;
  }

  p->top_ = p->cur_;
  p->cur_ += w;
  if (p->cur_ == p->end_) p->cur_ = p->start_;


  if (p->row_ >= 0 && p->row_ < p->height_ - 1) {
    p->src_ += p->width_;
  }
}
