createDTMFflow(AuServer *aud, AuDeviceID outputDevice, int volume, int duration)
{
    AuFlowID        flow;
    AuElement       elements[18];
    AuElementAction dev_act[2],
                    tone_act[1];
    unsigned short  inputs[8];
    int             elNum = 0,
                    i;
    AuFixedPoint    v = AuFixedPointFromFraction(1, 200 / volume);

    flow = AuCreateFlow(aud, NULL);

    AuMakeNoopAction(&tone_act[0], AuStateAny, AuStateAny, AuReasonAny);

    TONE(elNum, v, 697);
    TONE(elNum, v, 770);
    TONE(elNum, v, 852);
    TONE(elNum, v, 941);
    TONE(elNum, v, 1209);
    TONE(elNum, v, 1336);
    TONE(elNum, v, 1477);
    TONE(elNum, v, 1633);

    for (i = 0; i < 8; i++)
	inputs[i] = i * 2 + 1;

    AuMakeElementSum(&elements[elNum], 8, inputs);

    AuMakeChangeStateAction(&dev_act[0], AuStateStop, AuStateAny, AuReasonAny,
			    flow, AuElementAll, AuStateStop);
    AuMakeSendNotifyAction(&dev_act[1], AuStateStop, AuStateAny, AuReasonAny);

    AuMakeElementExportDevice(&elements[elNum + 1], elNum,
			      outputDevice, SAMPLE_RATE,
			      SAMPLE_RATE / 1000 * duration, 2, dev_act);


    AuSetElements(aud, flow, AuTrue, 18, elements, NULL);

    return flow;
}
