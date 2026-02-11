ompi_btl_usnic_setup_mpit_pvars(void)
{


    if (!setup_mpit_pvar_type()) {
        return OMPI_SUCCESS;
    }


    setup_mpit_pvars_enum();


    setup_mpit_pvars_highwatermark();


    if (!mca_btl_usnic_component.stats_relative) {
        setup_mpit_pvars_counters();
    }


    return OMPI_SUCCESS;
}
