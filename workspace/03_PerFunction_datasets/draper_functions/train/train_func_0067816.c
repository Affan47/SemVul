fluid_revmodel_update(fluid_revmodel_t* rev)
{

	int i;

	rev->wet1 = rev->wet * (rev->width / 2.0f + 0.5f);
	rev->wet2 = rev->wet * ((1.0f - rev->width) / 2.0f);

	for (i = 0; i < numcombs; i++) {
		fluid_comb_setfeedback(&rev->combL[i], rev->roomsize);
		fluid_comb_setfeedback(&rev->combR[i], rev->roomsize);
	}

	for (i = 0; i < numcombs; i++) {
		fluid_comb_setdamp(&rev->combL[i], rev->damp);
		fluid_comb_setdamp(&rev->combR[i], rev->damp);
	}
}
