sensor_LDCM(lsat_data * lsat)
{
    int i;


    int band[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    int code[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    double wmin[] = { 0.433, 0.450, 0.525, 0.630, 0.845, 1.560, 2.100, 0.500, 1.360, 10.3, 11.5 };
    double wmax[] = { 0.453, 0.515, 0.600, 0.680, 0.885, 1.660, 2.300, 0.680, 1.390, 11.3, 12.5 };


    strcpy(lsat->sensor, "OLI/TIRS");

    lsat->bands = 11;
    for (i = 0; i < lsat->bands; i++) {
	lsat->band[i].number = *(band + i);
	lsat->band[i].code = *(code + i);
	lsat->band[i].wavemax = *(wmax + i);
	lsat->band[i].wavemin = *(wmin + i);
	lsat->band[i].qcalmax = 255.;
	lsat->band[i].qcalmin = 1.;
	lsat->band[i].thermal = (lsat->band[i].number > 9 ? 1 : 0);
    }
    return;
}
