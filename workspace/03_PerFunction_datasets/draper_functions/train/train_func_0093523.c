imProcessSplitComplex(const imImage* src_image, imImage* dst_image1, imImage* dst_image2, int polar)
{
  int total_count = src_image->count*src_image->depth;

  imcfloat* map = (imcfloat*)src_image->data[0];
  float* map1 = (float*)dst_image1->data[0];
  float* map2 = (float*)dst_image2->data[0];

#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINCOUNT(total_count))
#endif
  for (int i = 0; i < total_count; i++)
  {
    if (polar)
    {
      map1[i] = cpxmag(map[i]);
      map2[i] = cpxphase(map[i]);
    }
    else
    {
      map1[i] = map[i].real;
      map2[i] = map[i].imag;
    }
  }
}
