sendClass1ECMData(const u_char* data, u_int cc, const u_char* bitrev, bool eod, u_int ppmcmd, Status& eresult)
{


    for (u_int i = 0; i < cc; i++) {
	if (ecmFramePos == 0) {
	    ecmFrame[ecmFramePos++] = 0xff;
	    ecmFrame[ecmFramePos++] = 0xc0;
	    ecmFrame[ecmFramePos++] = 0x60;
	    ecmFrame[ecmFramePos++] = frameRev[frameNumber++];
	}
	ecmFrame[ecmFramePos++] = frameRev[data[i]];
	if (ecmFramePos == (frameSize + 4)) {
	    bool lastframe = ((i == (cc - 1)) && eod);
	    if (!blockFrame(bitrev, lastframe, ppmcmd, eresult))
		return (false);
	    if (lastframe)
		return (true);
	}
    }
    if (eod) {
	if (ecmFramePos != 0)	{

	    while (ecmFramePos < (frameSize + 4)) ecmFrame[ecmFramePos++] = 0x00;
	}
	if (!blockFrame(bitrev, true, ppmcmd, eresult))
	    return (false);
    }
    return (true);
}
