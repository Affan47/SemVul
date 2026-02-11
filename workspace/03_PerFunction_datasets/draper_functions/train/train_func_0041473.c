gth_sa_collections_are_equal(const GthSACollection *sa_collectionA,
                                  const GthSACollection *sa_collectionB)
{
  GtArray *alignments_from_A, *alignments_from_B;
  unsigned long i;


  alignments_from_A = sa_collection_get_alignments(sa_collectionA);
  alignments_from_B = sa_collection_get_alignments(sa_collectionB);


  if (gt_array_size(alignments_from_A) != gt_array_size(alignments_from_B)) {
    gt_array_delete(alignments_from_A);
    gt_array_delete(alignments_from_B);
    return false;
  }


  for (i = 0; i < gt_array_size(alignments_from_A); i++) {
    if (!gth_sas_are_equal(*(GthSA**) gt_array_get(alignments_from_A, i),
                           *(GthSA**) gt_array_get(alignments_from_B, i))) {
      gt_array_delete(alignments_from_A);
      gt_array_delete(alignments_from_B);
      return false;
    }
  }


  gt_array_delete(alignments_from_A);
  gt_array_delete(alignments_from_B);

  return true;
}
