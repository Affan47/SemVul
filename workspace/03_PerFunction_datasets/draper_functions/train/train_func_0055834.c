gth_pgl_collection_new(GthSACollection *sacollection,
                                         bool disableclustersas)
{
  GthPGLCollection *pgl_collection;
  GthPGL *pgl;
  unsigned long i;
  gt_assert(sacollection);


  pgl_collection = gt_malloc(sizeof *pgl_collection);
  pgl_collection->pgls = gt_array_new(sizeof (GthPGL*));


  gthclusterSAstoPGLs(pgl_collection->pgls, sacollection);


  for (i = 0; i < gt_array_size(pgl_collection->pgls); i++) {
    pgl = *(GthPGL**) gt_array_get(pgl_collection->pgls, i);

    qsort(gt_array_get_space(pgl->alignments), gt_array_size(pgl->alignments),
          sizeof (GthSA*), gth_sa_cmp_genomic_actual);


    assemble_cluster(pgl, disableclustersas);


    gt_consensus_sa(gt_array_get_space(pgl->saclusters),
                    gt_array_size(pgl->saclusters),
                    sizeof (GthSACluster*), pgl_get_genomic_range,
                    pgl_get_strand, get_exons_func, process_splice_form_func,
                    pgl);
  }

  return pgl_collection;
}
