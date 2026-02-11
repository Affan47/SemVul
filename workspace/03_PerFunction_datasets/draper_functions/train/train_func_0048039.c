ath5k_eeprom_convert_pcal_info_2413(struct ath5k_hw *ah, int mode,
				struct ath5k_chan_pcal_info *chinfo)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info_rf2413 *pcinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	unsigned int pier, point;
	int pdg;


	for (pier = 0; pier < ee->ee_n_piers[mode]; pier++) {

		pcinfo = &chinfo[pier].rf2413_info;


		chinfo[pier].pd_curves =
				calloc(AR5K_EEPROM_N_PD_CURVES,
				       sizeof(struct ath5k_pdgain_info));

		if (!chinfo[pier].pd_curves)
			return -ENOMEM;


		for (pdg = 0; pdg < ee->ee_pd_gains[mode]; pdg++) {

			u8 idx = pdgain_idx[pdg];
			struct ath5k_pdgain_info *pd =
					&chinfo[pier].pd_curves[idx];


			if (pdg == ee->ee_pd_gains[mode] - 1)
				pd->pd_points = AR5K_EEPROM_N_PD_POINTS;
			else
				pd->pd_points = AR5K_EEPROM_N_PD_POINTS - 1;


			pd->pd_step = calloc(pd->pd_points, sizeof(u8));

			if (!pd->pd_step)
				return -ENOMEM;

			pd->pd_pwr = calloc(pd->pd_points, sizeof(s16));

			if (!pd->pd_pwr)
				return -ENOMEM;


			pd->pd_step[0] = pcinfo->pddac_i[pdg];
			pd->pd_pwr[0] = 4 * pcinfo->pwr_i[pdg];

			for (point = 1; point < pd->pd_points; point++) {

				pd->pd_pwr[point] = pd->pd_pwr[point - 1] +
					2 * pcinfo->pwr[pdg][point - 1];

				pd->pd_step[point] = pd->pd_step[point - 1] +
						pcinfo->pddac[pdg][point - 1];

			}


			if (pdg == 0)
				chinfo[pier].min_pwr = pd->pd_pwr[0];


			if (pdg == ee->ee_pd_gains[mode] - 1)
				chinfo[pier].max_pwr =
					pd->pd_pwr[pd->pd_points - 1];
		}
	}

	return 0;
}
