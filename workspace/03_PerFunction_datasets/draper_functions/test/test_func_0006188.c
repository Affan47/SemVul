mgicchikn_rc_parse_shadow (MgicChiknRcStyle * style,
						   GScanner * scanner)
{
	MgicChiknShadowType shadow_type;
	gboolean state_mask[GTK_STATE_LAST],
	  shadow_mask[MGICCHIKN_SHADOW_LAST];
	guint token,
	  i,
	  i2;

	token = mgicchikn_rc_parse_state_shadow_equals (scanner, state_mask, shadow_mask);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	switch (token)
	{
	case MGICCHIKN_TOKEN_NONE:
		shadow_type = MGICCHIKN_SHADOW_NONE;
		break;
	case MGICCHIKN_TOKEN_IN:
		shadow_type = MGICCHIKN_SHADOW_IN;
		break;
	case MGICCHIKN_TOKEN_OUT:
		shadow_type = MGICCHIKN_SHADOW_OUT;
		break;

	case MGICCHIKN_TOKEN_ETCHED_IN:
		shadow_type = MGICCHIKN_SHADOW_ETCHED_IN;
		break;
	case MGICCHIKN_TOKEN_ETCHED_OUT:
		shadow_type = MGICCHIKN_SHADOW_ETCHED_OUT;
		break;

	case MGICCHIKN_TOKEN_FLAT:
		shadow_type = MGICCHIKN_SHADOW_FLAT;
		break;

	case MGICCHIKN_TOKEN_SHARP_IN:
		shadow_type = MGICCHIKN_SHADOW_SHARP_IN;
		break;
	case MGICCHIKN_TOKEN_SHARP_OUT:
		shadow_type = MGICCHIKN_SHADOW_SHARP_OUT;
		break;

	case MGICCHIKN_TOKEN_ROUNDED_IN:
		shadow_type = MGICCHIKN_SHADOW_ROUNDED_IN;
		break;
	case MGICCHIKN_TOKEN_ROUNDED_OUT:
		shadow_type = MGICCHIKN_SHADOW_ROUNDED_OUT;
		break;

	case MGICCHIKN_TOKEN_MOTIF_IN:
		shadow_type = MGICCHIKN_SHADOW_MOTIF_IN;
		break;
	case MGICCHIKN_TOKEN_MOTIF_OUT:
		shadow_type = MGICCHIKN_SHADOW_MOTIF_OUT;
		break;
	default:
		return MGICCHIKN_TOKEN_IN;
		break;
	}


	for (i = 0; i < GTK_STATE_LAST; i++)
	{
		if (state_mask[i])
		{
			for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i2++)
			{
				if (shadow_mask[i2])
				{
					style->shadow[i][i2] = shadow_type;
				}
			}
		}
	}

	return G_TOKEN_NONE;
}
