smSingmasterFaceIDSeen (const SingmasterMove smCode)
{
    switch (smCode) {
    case SM_INNER:
	executeSingmasterMove (SM_EXECUTE);
	smDotCount = 1;
	smTempString = SingmasterNotation [SM_INNER];
	keyboardState = SingmasterPrefixSeen;
	break;
    case SM_ANTICLOCKWISE:
    case SM_DOUBLE:
    case SM_2_SLICE:
    case SM_ANTISLICE:
    case SM_EXECUTE:
	executeSingmasterMove (smCode);
	keyboardState = WaitingForInput;
	break;
    case SM_SPACER:
	executeSingmasterMove (smCode);
	keyboardState = WaitingForInput;
	break;
    case SM_UP:
    case SM_DOWN:
    case SM_LEFT:
    case SM_RIGHT:
    case SM_FRONT:
    case SM_BACK:
	executeSingmasterMove (SM_EXECUTE);
	saveSingmasterFaceID (smCode);
	keyboardState = SingmasterFaceIDSeen;
	break;
    default:
	kDebug() << "Unknown Singmaster code" << smCode;
	break;
    }
}
