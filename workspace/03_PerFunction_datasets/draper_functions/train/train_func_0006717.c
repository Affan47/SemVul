lower_dim_size_comp_test(void)
{

    int		chunk_edge_size = 0;
    int  	use_collective_io = 1;
    hid_t	dset_type = H5T_NATIVE_UINT;
#if 0
   sleep(60);
#endif
    HDcompile_assert(sizeof(uint32_t) == sizeof(unsigned));
    for ( use_collective_io = (hbool_t)0;
          (int)use_collective_io <= 1;
          (hbool_t)(use_collective_io++) ) {

        chunk_edge_size = 0;
        lower_dim_size_comp_test__run_test(chunk_edge_size,
                                           (hbool_t)use_collective_io,
                                           dset_type);


        chunk_edge_size = 5;
        lower_dim_size_comp_test__run_test(chunk_edge_size,
                                           (hbool_t)use_collective_io,
                                           dset_type);
    }

    return;

}
