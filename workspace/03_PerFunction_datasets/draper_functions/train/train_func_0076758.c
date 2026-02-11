ompi_coll_tuned_barrier_intra_check_forced_init (coll_tuned_force_algorithm_mca_param_indices_t *mca_param_indices)
{
    mca_base_var_enum_t *new_enum;

    ompi_coll_tuned_forced_max_algorithms[BARRIER] = coll_tuned_barrier_algorithm_count;

    (void) mca_base_component_var_register(&mca_coll_tuned_component.super.collm_version,
                                           "barrier_algorithm_count",
                                           "Number of barrier algorithms available",
                                           MCA_BASE_VAR_TYPE_INT, NULL, 0,
                                           MCA_BASE_VAR_FLAG_DEFAULT_ONLY,
                                           OPAL_INFO_LVL_5,
                                           MCA_BASE_VAR_SCOPE_CONSTANT,
                                           &coll_tuned_barrier_algorithm_count);


    coll_tuned_barrier_forced_algorithm = 0;
    (void) mca_base_var_enum_create("coll_tuned_barrier_algorithms", barrier_algorithms, &new_enum);
    mca_param_indices->algorithm_param_index =
        mca_base_component_var_register(&mca_coll_tuned_component.super.collm_version,
                                        "barrier_algorithm",
                                        "Which barrier algorithm is used. Can be locked down to choice of: 0 ignore, 1 linear, 2 double ring, 3: recursive doubling 4: bruck, 5: two proc only, 6: tree",
                                        MCA_BASE_VAR_TYPE_INT, new_enum, 0, 0,
                                        OPAL_INFO_LVL_5,
                                        MCA_BASE_VAR_SCOPE_READONLY,
                                        &coll_tuned_barrier_forced_algorithm);
    OBJ_RELEASE(new_enum);
    if (mca_param_indices->algorithm_param_index < 0) {
        return mca_param_indices->algorithm_param_index;
    }

    return (MPI_SUCCESS);
}
