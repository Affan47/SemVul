grid_open_cartesian(const BasisInfoStruct& bis,
		    const Dft::GridParams& gss,
                    const Dft::Matrix* dmat,
                    Dft::SparsePattern *pattern, DftGridReader *reader)
{
  pthread_mutex_lock(&grdone_mutex);
  if (!grid_file_name) {
    grid_file_name = grid_get_fname(GRID_BASE_NAME, MY_MPI_NUM);
    hicu_grid_generate(grid_file_name, bis,
		       gss.hicuParams.maxError,
		       gss.hicuParams.box_size,
		       gss.hicuParams.start_box_size_debug,
		       gss.hicuParams.use_error_per_volume,
		       gss.hicuParams.do_double_checking,
		       gss.hicuParams.compare_to_refined,
		       gss.hicuParams.use_energy_criterion,
		       gss.hicuParams.use_energy_criterion_only,
		       gss.hicuParams.do_variation_checking,
                       dmat, pattern, dft_get_num_threads(), false);
    if(pattern) {
      patt_file_name = grid_get_fname(GRID_PATT_NAME, MY_MPI_NUM);
      FILE  *f;
      if( (f = fopen(patt_file_name, "wb")) == NULL)
        throw "Cannot open pattern file for writing";
      pattern->save(f);
      if(fclose(f) != 0)
        throw "Cannot close the sparse pattern file";
    }
  }

  if(pattern) {
    FILE  *f;
    if(!patt_file_name)
      throw "Dft::SparsePattern requested but unavailable.";
    if( (f = fopen(patt_file_name, "rb")) == NULL)
      throw "Cannot open pattern file for reading";
    pattern->load(f);
    if(fclose(f) != 0)
      throw "Cannot close the sparse pattern file";
  }

  if(!grid_file)
    grid_file = fopen(grid_file_name, "rb");
  grid_file_open_count++;
  pthread_mutex_unlock(&grdone_mutex);
  reader->f= grid_file;
  if(grid_file == NULL) {
    perror("grid_open_cartesian: DFT quadrature grid file " GRID_BASE_NAME
           " not found");
    free(reader);
    abort();
  }
}
