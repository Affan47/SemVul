fsvOpClassAdmin(
	FSV_WIRE *	pWire)
{
	RCODE 		opRc = FERR_OK;
	RCODE 		rc = FERR_OK;

	opRc = RC_SET( FERR_NOT_IMPLEMENTED);
	goto OP_EXIT;

OP_EXIT:


	if (RC_BAD( rc = pWire->sendOpcode( FCS_OPCLASS_ADMIN, pWire->getOp())))
	{
		goto Exit;
	}

	if (RC_BAD( rc = pWire->sendRc( opRc)))
	{
		goto Exit;
	}

	if (RC_BAD( rc = pWire->sendTerminate()))
	{
		goto Exit;
	}

Exit:

	return (rc);
}
