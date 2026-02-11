recvTraining()
{
    if (useV34) {
	sendCFR = true;
	return (true);
    }


    if (!atCmd(conf.class1TCFRecvHackCmd, AT_OK)) {
	return (false);
    }

    protoTrace("RECV training at %s %s",
	modulationNames[curcap->mod],
	Class2Params::bitRateNames[curcap->br]);
    HDLCFrame buf(conf.class1FrameOverhead);
    bool ok = recvTCF(curcap->value, buf, frameRev, conf.class1TCFRecvTimeout);
    if (ok) {
	u_int n = buf.getLength();
	u_int nonzero = 0;
	u_int zerorun = 0;
	u_int i = 0;


	while (i < n && buf[i] != 0)
	    i++;


	if (i < n) {
	    while (i < n) {
		u_int j;
		for (; i < n && buf[i] != 0; i++)
		    nonzero++;
		for (j = i; j < n && buf[j] == 0; j++)
		    ;
		if (j-i > zerorun)
		    zerorun = j-i;
		i = j;
	    }
	} else {


	    nonzero = n;
	}


	u_int fullrun = params.transferSize(TCF_DURATION);
	u_int minrun = params.transferSize(conf.class1TCFMinRun);
	if (params.ec != EC_DISABLE && conf.class1TCFMinRunECMMod > 0) {


	    minrun /= conf.class1TCFMinRunECMMod;
	}
	nonzero = (100*nonzero) / (n == 0 ? 1 : n);
	protoTrace("RECV: TCF %u bytes, %u%% non-zero, %u zero-run",
	    n, nonzero, zerorun);
	if (zerorun < fullrun && nonzero > conf.class1TCFMaxNonZero) {
	    protoTrace("RECV: reject TCF (too many non-zero, max %u%%)",
		conf.class1TCFMaxNonZero);
	    ok = false;
	}
	if (zerorun < minrun) {
	    protoTrace("RECV: reject TCF (zero run too short, min %u)", minrun);
	    ok = false;
	}
	if (!wasTimeout()) {


	    time_t nocarrierstart = Sys::now();
	    bool gotnocarrier = false;
	    do {
		gotnocarrier = waitFor(AT_NOCARRIER, 2*1000);
	    } while (!gotnocarrier && Sys::now() < (nocarrierstart + 5));
	}
    } else {

	if (lastResponse == AT_FCERROR && atCmd(rhCmd, AT_NOTHING)) lastResponse = AT_FRH3;
	if (lastResponse == AT_FRH3) return (false);
    }


    Status eresult;
    if (!switchingPause(eresult)) return (false);
    if (ok) {


	sendCFR = true;
	protoTrace("TRAINING succeeded");
    } else {
	transmitFrame(FCF_FTT|FCF_RCVR);
	sendCFR = false;
	protoTrace("TRAINING failed");
    }
    return (ok);
}
