sort_matches_and_calc_buckets(GtArray *matches, GtArray *buckets,
                                          unsigned long *maxbucketlength)
{
  unsigned long i, currentstart = 0, currentend = 0;
  GthMatch *matchptr;
  Bucket bucket, *bucketptr;

  gt_assert(gt_array_size(matches));


  qsort(gt_array_get_space(matches), gt_array_size(matches), sizeof (GthMatch),
        compare_matches);


  matchptr = gt_array_get_first(matches);
  bucket.seqnum1  = matchptr->Storeseqnumreference;
  bucket.seqnum2  = matchptr->Storeseqnumgenomic;
  bucket.startpos = 0;


  for (i = 1; i < gt_array_size(matches); i++) {
    matchptr = gt_array_get(matches, i);
    if (matchptr->Storeseqnumreference != bucket.seqnum1 ||
        matchptr->Storeseqnumgenomic != bucket.seqnum2) {

      currentend    = i - 1;
      bucket.length = currentend - currentstart + 1;
      gt_array_add(buckets, bucket);


      currentstart    = i;
      bucket.seqnum1  = matchptr->Storeseqnumreference;
      bucket.seqnum2  = matchptr->Storeseqnumgenomic;
      bucket.startpos = i;
    }
  }


  currentend = i - 1;
  bucket.length = currentend - currentstart + 1;
  gt_array_add(buckets, bucket);


  *maxbucketlength = 0;
  for (i = 0; i < gt_array_size(buckets); i++) {
    bucketptr = gt_array_get(buckets, i);
    if (bucketptr->length > *maxbucketlength)
      *maxbucketlength = bucketptr->length;
  }

  gt_assert(sum_of_bucket_lengths_equals_num_of_matches(buckets,
                                                     gt_array_size(matches)));
}
