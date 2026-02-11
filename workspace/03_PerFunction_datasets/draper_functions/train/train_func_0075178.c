encdesc_gt_xfread(void *ptr,
                                      size_t size,
                                      size_t nmemb,
                                      FILE *stream)
{
  GT_UNUSED size_t written;
  written = gt_xfread(ptr, size, nmemb, stream);
  gt_assert(written == nmemb);
}
