exp_arm_background_channelhandler(esPtr)
ExpState *esPtr;
{
    switch (esPtr->bg_status) {
	case unarmed:
	    exp_arm_background_channelhandler_force(esPtr);
	    break;
	case disarm_req_while_blocked:
	    esPtr->bg_status = blocked;
	    break;
	case armed:
	case blocked:

	    break;
    }
}
