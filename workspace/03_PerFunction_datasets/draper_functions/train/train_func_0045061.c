gthfilestat_process_files(GthFileStatInfo *file_stat_info,
                                     const GthPlugins *plugins, GtError *err)
{
  GthSACollection *sa_collection;
  GthStat *stat;
  GthInput *input;
  GthPGLCollection *pgl_collection = NULL;
  int had_err = 0;

  gt_error_check(err);


  sa_collection = gth_sa_collection_new(GTH_DC_NONE);
  input = gth_input_new(plugins->file_preprocessor, plugins->seq_con_new);
  stat = gth_stat_new();
  gth_stat_enable_sa_stats(stat);
  gth_stat_enable_gthfilestat_mode(stat);

  if (file_stat_info->showverbose)
    file_stat_info->showverbose("process all intermediate output files");


  had_err = gth_build_sa_collection(sa_collection, input,
                                    file_stat_info->consensusfiles,
                                    file_stat_info->sa_filter, stat,
                                    file_stat_info->showverbose, err);

  if (!had_err && gth_sa_collection_contains_sa(sa_collection)) {

    pgl_collection = gth_pgl_collection_new(sa_collection, false);


    gth_stat_increase_numofPGLs_stored(stat,
                                       gth_pgl_collection_size(pgl_collection));
  }


  gth_stat_show(stat, false, false, NULL);


  gth_sa_collection_delete(sa_collection);
  gth_input_delete_complete(input);
  gth_stat_delete(stat);
  gth_pgl_collection_delete(pgl_collection);

  return had_err;
}
