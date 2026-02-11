p54_get_maxpower(struct p54_common *priv, void *data)
{
	switch (priv->rxhw & PDR_SYNTH_FRONTEND_MASK) {
	case PDR_SYNTH_FRONTEND_LONGBOW: {
		struct pda_channel_output_limit_longbow *pda = data;
		int j;
		u16 rawpower = 0;
		pda = data;
		for (j = 0; j < ARRAY_SIZE(pda->point); j++) {
			struct pda_channel_output_limit_point_longbow *point =
				&pda->point[j];
			rawpower = max_t(u16,
				rawpower, le16_to_cpu(point->val_qpsk));
			rawpower = max_t(u16,
				rawpower, le16_to_cpu(point->val_bpsk));
			rawpower = max_t(u16,
				rawpower, le16_to_cpu(point->val_16qam));
			rawpower = max_t(u16,
				rawpower, le16_to_cpu(point->val_64qam));
		}

		return rawpower / 16;
		}

	case PDR_SYNTH_FRONTEND_DUETTE3:
	case PDR_SYNTH_FRONTEND_DUETTE2:
	case PDR_SYNTH_FRONTEND_FRISBEE:
	case PDR_SYNTH_FRONTEND_XBOW: {
		struct pda_channel_output_limit *pda = data;
		u8 rawpower = 0;
		rawpower = max(rawpower, pda->val_qpsk);
		rawpower = max(rawpower, pda->val_bpsk);
		rawpower = max(rawpower, pda->val_16qam);
		rawpower = max(rawpower, pda->val_64qam);

		return rawpower / 4;
		}

	default:
		return 20;
	}
}
