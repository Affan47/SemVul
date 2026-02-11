qh_initqhull_mem (void) {
  int numsizes;
  int i;

  numsizes= 7+10;
  qh_meminitbuffers (qh IStracing, qh_MEMalign, numsizes,
                     qh_MEMbufsize,qh_MEMinitbuf);
  qh_memsize(sizeof(vertexT));
  if (qh MERGING)
    qh_memsize(sizeof(ridgeT));
  qh_memsize(sizeof(facetT));
  qh_memsize(sizeof(hashentryT));
  i= sizeof(setT) + (qh hull_dim - 1) * SETelemsize;
  qh_memsize(i);
  qh_memsize(qh normal_size);
  i += SETelemsize;
  qh_memsize(i);

  qh_memsetup();
}
