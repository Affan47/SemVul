amdgpu_atombios_crtc_program_ss(struct amdgpu_device *adev,
				     int enable,
				     int pll_id,
				     int crtc_id,
				     struct amdgpu_atom_ss *ss)
{
	unsigned i;
	int index = GetIndexIntoMasterTable(COMMAND, EnableSpreadSpectrumOnPPLL);
	union atom_enable_ss args;

	if (enable) {


		if (ss->percentage == 0)
			return;
		if (ss->type & ATOM_EXTERNAL_SS_MASK)
			return;
	} else {
		for (i = 0; i < adev->mode_info.num_crtc; i++) {
			if (adev->mode_info.crtcs[i] &&
			    adev->mode_info.crtcs[i]->enabled &&
			    i != crtc_id &&
			    pll_id == adev->mode_info.crtcs[i]->pll_id) {


				return;
			}
		}
	}

	memset(&args, 0, sizeof(args));

	args.v3.usSpreadSpectrumAmountFrac = cpu_to_le16(0);
	args.v3.ucSpreadSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
	switch (pll_id) {
	case ATOM_PPLL1:
		args.v3.ucSpreadSpectrumType |= ATOM_PPLL_SS_TYPE_V3_P1PLL;
		break;
	case ATOM_PPLL2:
		args.v3.ucSpreadSpectrumType |= ATOM_PPLL_SS_TYPE_V3_P2PLL;
		break;
	case ATOM_DCPLL:
		args.v3.ucSpreadSpectrumType |= ATOM_PPLL_SS_TYPE_V3_DCPLL;
		break;
	case ATOM_PPLL_INVALID:
		return;
	}
	args.v3.usSpreadSpectrumAmount = cpu_to_le16(ss->amount);
	args.v3.usSpreadSpectrumStep = cpu_to_le16(ss->step);
	args.v3.ucEnable = enable;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);
}
