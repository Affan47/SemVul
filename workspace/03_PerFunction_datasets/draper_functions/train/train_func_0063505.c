others(void)
{
    int i;


    misc.Qt_mean = 0.0;
    for (i = 0; i < input.ntimestep; i++) {
	misc.Qt_mean += misc.Qt[i];
	if (!i || misc.Qt_peak < misc.Qt[i]) {
	    misc.Qt_peak = misc.Qt[i];
	    misc.tt_peak = i + 1;
	}
    }
    misc.Qt_mean /= input.ntimestep;

    if (file.Qobs) {
	misc.Em = get_Em();
	for (i = 0; i < input.ntimestep; i++) {
	    if (!i || misc.Qobs_peak < misc.Qobs[i]) {
		misc.Qobs_peak = misc.Qobs[i];
		misc.tobs_peak = i + 1;
	    }
	}
    }


    return;
}
