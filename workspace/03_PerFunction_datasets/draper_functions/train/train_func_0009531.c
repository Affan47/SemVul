bcol_base_module_destructor(mca_bcol_base_module_t *module)
{
    int fnc;

    module->bcol_component = NULL;

    module->context_index = -1;
    module->init_module = NULL;
    module->sbgp_partner_module = NULL;
    module->squence_number_offset = 0;
    module->n_poll_loops = 0;

    for (fnc = 0; fnc < BCOL_NUM_OF_FUNCTIONS; fnc++) {
        module->bcol_function_table[fnc] = NULL;
    }

    module->bcol_memory_init = NULL;
}
