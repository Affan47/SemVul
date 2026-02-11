opj_set_default_encoder_parameters(opj_cparameters_t *parameters) {
	if(parameters) {
		memset(parameters, 0, sizeof(opj_cparameters_t));

		parameters->cp_cinema = OFF;
		parameters->max_comp_size = 0;
		parameters->numresolution = 6;
		parameters->cp_rsiz = STD_RSIZ;
		parameters->cblockw_init = 64;
		parameters->cblockh_init = 64;
		parameters->prog_order = LRCP;
		parameters->roi_compno = -1;
		parameters->subsampling_dx = 1;
		parameters->subsampling_dy = 1;
		parameters->tp_on = 0;
		parameters->decod_format = -1;
		parameters->cod_format = -1;
		parameters->tcp_rates[0] = 0;
		parameters->tcp_numlayers = 0;
    parameters->cp_disto_alloc = 0;
		parameters->cp_fixed_alloc = 0;
		parameters->cp_fixed_quality = 0;
		parameters->jpip_on = OPJ_FALSE;

#ifdef USE_JPWL
		parameters->jpwl_epc_on = OPJ_FALSE;
		parameters->jpwl_hprot_MH = -1;
		{
			int i;
			for (i = 0; i < JPWL_MAX_NO_TILESPECS; i++) {
				parameters->jpwl_hprot_TPH_tileno[i] = -1;
				parameters->jpwl_hprot_TPH[i] = 0;
			}
		};
		{
			int i;
			for (i = 0; i < JPWL_MAX_NO_PACKSPECS; i++) {
				parameters->jpwl_pprot_tileno[i] = -1;
				parameters->jpwl_pprot_packno[i] = -1;
				parameters->jpwl_pprot[i] = 0;
			}
		};
		parameters->jpwl_sens_size = 0;
		parameters->jpwl_sens_addr = 0;
		parameters->jpwl_sens_range = 0;
		parameters->jpwl_sens_MH = -1;
		{
			int i;
			for (i = 0; i < JPWL_MAX_NO_TILESPECS; i++) {
				parameters->jpwl_sens_TPH_tileno[i] = -1;
				parameters->jpwl_sens_TPH[i] = -1;
			}
		};
#endif

	}
}
