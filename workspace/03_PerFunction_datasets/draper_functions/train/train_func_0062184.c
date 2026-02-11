vs_fill_borders_Y (const VSImage * dest, const uint8_t * val)
{
  int i;
  int top = dest->border_top, bottom = dest->border_bottom;
  int left = dest->border_left, right = dest->border_right;
  int width = dest->width;
  int height = dest->height;
  int real_width = dest->real_width;
  int stride = dest->stride;
  int tmp, tmp2;
  uint8_t *data;

  data = dest->real_pixels;
  for (i = 0; i < top; i++) {
    memset (data, *val, real_width);
    data += stride;
  }

  if (left || right) {
    tmp = height;
    tmp2 = left + width;
    for (i = 0; i < tmp; i++) {
      memset (data, *val, left);
      memset (data + tmp2, *val, right);
      data += stride;
    }
  } else {
    data += stride * height;
  }

  for (i = 0; i < bottom; i++) {
    memset (data, *val, real_width);
    data += stride;
  }
}
