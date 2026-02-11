test_sohm_extend_dset(void)
{
    hid_t fcpl_id = -1;
    herr_t ret;


    fcpl_id = H5Pcreate(H5P_FILE_CREATE);
    CHECK_I(fcpl_id, "H5Pcreate");


    ret = H5Pset_shared_mesg_nindexes(fcpl_id, 1);
    CHECK_I(ret, "H5Pset_shared_mesg_nindexes");


    ret = test_sohm_extend_dset_helper(fcpl_id, FALSE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");
    ret = test_sohm_extend_dset_helper(fcpl_id, TRUE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");


    ret = H5Pset_shared_mesg_index(fcpl_id, 0, H5O_SHMESG_SDSPACE_FLAG, 16);
    CHECK_I(ret, "H5Pset_shared_mesg_index");

    ret = test_sohm_extend_dset_helper(fcpl_id, FALSE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");
    ret = test_sohm_extend_dset_helper(fcpl_id, TRUE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");


    ret = H5Pset_shared_mesg_nindexes(fcpl_id, 1);
    CHECK_I(ret, "H5Pset_shared_mesg_nindexes");
    ret = H5Pset_shared_mesg_index(fcpl_id, 0, H5O_SHMESG_ALL_FLAG, 16);
    CHECK_I(ret, "H5Pset_shared_mesg_index");

    ret = test_sohm_extend_dset_helper(fcpl_id, FALSE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");
    ret = test_sohm_extend_dset_helper(fcpl_id, TRUE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");


    ret = H5Pset_shared_mesg_phase_change(fcpl_id, 100, 50);
    CHECK_I(ret, "H5Pset_shared_mesg_phase_change");

    ret = test_sohm_extend_dset_helper(fcpl_id, FALSE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");
    ret = test_sohm_extend_dset_helper(fcpl_id, TRUE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");


    ret = H5Pset_shared_mesg_phase_change(fcpl_id, 1, 0);
    CHECK_I(ret, "H5Pset_shared_mesg_phase_change");

    ret = test_sohm_extend_dset_helper(fcpl_id, FALSE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");
    ret = test_sohm_extend_dset_helper(fcpl_id, TRUE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");


    ret = H5Pset_shared_mesg_phase_change(fcpl_id, 0, 0);
    CHECK_I(ret, "H5Pset_shared_mesg_phase_change");

    ret = test_sohm_extend_dset_helper(fcpl_id, FALSE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");
    ret = test_sohm_extend_dset_helper(fcpl_id, TRUE);
    CHECK_I(ret, "test_sohm_extend_dset_helper");

    ret = H5Pclose(fcpl_id);
    CHECK_I(ret, "H5Pclose");
}
