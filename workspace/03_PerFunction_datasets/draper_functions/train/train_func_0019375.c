WebPPictureCopy(const WebPPicture* src, WebPPicture* dst) {
  if (src == NULL || dst == NULL) return 0;
  if (src == dst) return 1;

  PictureGrabSpecs(src, dst);
  if (!WebPPictureAlloc(dst)) return 0;

  if (!src->use_argb) {
    CopyPlane(src->y, src->y_stride,
              dst->y, dst->y_stride, dst->width, dst->height);
    CopyPlane(src->u, src->uv_stride,
              dst->u, dst->uv_stride, HALVE(dst->width), HALVE(dst->height));
    CopyPlane(src->v, src->uv_stride,
              dst->v, dst->uv_stride, HALVE(dst->width), HALVE(dst->height));
    if (dst->a != NULL)  {
      CopyPlane(src->a, src->a_stride,
                dst->a, dst->a_stride, dst->width, dst->height);
    }
  } else {
    CopyPlane((const uint8_t*)src->argb, 4 * src->argb_stride,
              (uint8_t*)dst->argb, 4 * dst->argb_stride,
              4 * dst->width, dst->height);
  }
  return 1;
}
