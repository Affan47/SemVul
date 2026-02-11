ompi_coll_tuned_bcast_intra_chain( void* buffer,
                                   int count,
                                   struct ompi_datatype_t* datatype,
                                   int root,
                                   struct ompi_communicator_t* comm,
                                   mca_coll_base_module_t *module,
                                   uint32_t segsize, int32_t chains )
{
    int segcount = count;
    size_t typelng;
    mca_coll_tuned_module_t *tuned_module = (mca_coll_tuned_module_t*) module;
    mca_coll_tuned_comm_t *data = tuned_module->tuned_data;

    COLL_TUNED_UPDATE_CHAIN( comm, tuned_module, root, chains );


    ompi_datatype_type_size( datatype, &typelng );
    COLL_TUNED_COMPUTED_SEGCOUNT( segsize, typelng, segcount );

    OPAL_OUTPUT((ompi_coll_tuned_stream,"coll:tuned:bcast_intra_chain rank %d fo %d ss %5d typelng %lu segcount %d",
                 ompi_comm_rank(comm), chains, segsize, (unsigned long)typelng, segcount));

    return ompi_coll_tuned_bcast_intra_generic( buffer, count, datatype, root, comm, module,
                                                segcount, data->cached_chain );
}
