dna_exop_init(Slapi_PBlock * pb)
{
    int status = DNA_SUCCESS;

    if (slapi_pblock_set(pb, SLAPI_PLUGIN_VERSION,
                         SLAPI_PLUGIN_VERSION_01) != 0 ||
        slapi_pblock_set(pb, SLAPI_PLUGIN_DESCRIPTION,
                         (void *) &exop_pdesc) != 0 ||
        slapi_pblock_set(pb, SLAPI_PLUGIN_EXT_OP_OIDLIST,
                         (void *) dna_extend_exop_oid_list) != 0 ||
        slapi_pblock_set(pb, SLAPI_PLUGIN_EXT_OP_FN,
                         (void *) dna_extend_exop) != 0) {
        slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                        "dna_exop_init: failed to register plugin\n");
        status = DNA_FAILURE;
    }

    return status;
}
