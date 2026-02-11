TestPageHeap_Limit() {
  tcmalloc::PageHeap* ph = new tcmalloc::PageHeap();

  CHECK_EQ(kMaxPages, 1 << (20 - kPageShift));


  {
    FLAGS_tcmalloc_heap_limit_mb = 1;
    tcmalloc::Span* s = NULL;
    while((s = ph->New(kMaxPages)) == NULL) {
      FLAGS_tcmalloc_heap_limit_mb++;
    }
    FLAGS_tcmalloc_heap_limit_mb += 9;
    ph->Delete(s);

  }


  {
    tcmalloc::Span * spans[10];
    for (int i=0; i<10; ++i) {
      spans[i] = ph->New(kMaxPages);
      EXPECT_NE(spans[i], NULL);
    }
    EXPECT_EQ(ph->New(kMaxPages), NULL);

    for (int i=0; i<10; i += 2) {
      ph->Delete(spans[i]);
    }

    tcmalloc::Span *defragmented = ph->New(5 * kMaxPages);

    if (HaveSystemRelease) {

      EXPECT_NE(defragmented, NULL);
      EXPECT_TRUE(ph->CheckExpensive());
      ph->Delete(defragmented);
    }
    else
    {
      EXPECT_EQ(defragmented, NULL);
      EXPECT_TRUE(ph->CheckExpensive());
    }

    for (int i=1; i<10; i += 2) {
      ph->Delete(spans[i]);
    }
  }


  {
    tcmalloc::Span * spans[20];
    for (int i=0; i<20; ++i) {
      spans[i] = ph->New(kMaxPages >> 1);
      EXPECT_NE(spans[i], NULL);
    }

    tcmalloc::Span * lastHalf = ph->New(kMaxPages >> 1);
    EXPECT_EQ(ph->New(kMaxPages >> 1), NULL);

    for (int i=0; i<20; i += 2) {
      ph->Delete(spans[i]);
    }

    for(Length len = kMaxPages >> 2; len < 5 * kMaxPages; len = len << 1)
    {
      if(len <= kMaxPages >> 1 || HaveSystemRelease) {
        tcmalloc::Span *s = ph->New(len);
        EXPECT_NE(s, NULL);
        ph->Delete(s);
      }
    }

    EXPECT_TRUE(ph->CheckExpensive());

    for (int i=1; i<20; i += 2) {
      ph->Delete(spans[i]);
    }

    if (lastHalf != NULL) {
      ph->Delete(lastHalf);
    }
  }

  delete ph;
}
