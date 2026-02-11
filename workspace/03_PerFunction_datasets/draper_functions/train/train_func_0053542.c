bioseq_fill(GtBioseq *bs, bool recreate, GtError *err)
{
  GtStr *bioseq_index_file = NULL,
        *bioseq_ois_file = NULL,
        *bioseq_sds_file = NULL,
        *bioseq_md5_file = NULL,
        *bioseq_des_file = NULL;
  int had_err = 0;

  gt_assert(!bs->encseq);


  bioseq_index_file = gt_str_clone(bs->sequence_file);
  gt_str_append_cstr(bioseq_index_file, GT_ENCSEQFILESUFFIX);
  bioseq_ois_file = gt_str_clone(bs->sequence_file);
  gt_str_append_cstr(bioseq_ois_file, GT_OISTABFILESUFFIX);
  bioseq_sds_file = gt_str_clone(bs->sequence_file);
  gt_str_append_cstr(bioseq_sds_file, GT_SDSTABFILESUFFIX);
  bioseq_md5_file = gt_str_clone(bs->sequence_file);
  gt_str_append_cstr(bioseq_md5_file, GT_MD5TABFILESUFFIX);
  bioseq_des_file = gt_str_clone(bs->sequence_file);
  gt_str_append_cstr(bioseq_des_file, GT_DESTABFILESUFFIX);


  if (recreate || bs->use_stdin ||
      !gt_file_exists(gt_str_get(bioseq_index_file)) ||
      !gt_file_exists(gt_str_get(bioseq_ois_file)) ||
      !gt_file_exists(gt_str_get(bioseq_sds_file)) ||
      !gt_file_exists(gt_str_get(bioseq_md5_file)) ||
      !gt_file_exists(gt_str_get(bioseq_des_file)) ||
      gt_file_is_newer(gt_str_get(bs->sequence_file),
                       gt_str_get(bioseq_index_file))) {
    had_err = construct_bioseq_files(bs, bs->sequence_file, err);
  }

  if (!had_err) {
    GtEncseqLoader *el = gt_encseq_loader_new();
    gt_encseq_loader_disable_autosupport(el);
    gt_encseq_loader_require_lossless_support(el);
    gt_encseq_loader_require_description_support(el);
    gt_encseq_loader_require_md5_support(el);
    gt_encseq_loader_require_multiseq_support(el);
    bs->encseq = gt_encseq_loader_load(el, gt_str_get(bs->sequence_file), err);
    if (bs->encseq == NULL) {
      had_err = -1;
      gt_assert(gt_error_is_set(err));
    }
    gt_encseq_loader_delete(el);
  }
  if (!had_err) {
    gt_assert(bs->encseq);
  }


  gt_str_delete(bioseq_index_file);
  gt_str_delete(bioseq_ois_file);
  gt_str_delete(bioseq_md5_file);
  gt_str_delete(bioseq_sds_file);
  gt_str_delete(bioseq_des_file);

  return had_err;
}
