reallyDisconnect()


{
    if (flags.fromEngine || flags.converted) {
	SoEngineOutput *out = auditorInfo->connection.engineOutput;
	out->removeConnection(this);
	auditorInfo->connection.engineOutput = NULL;
    }
    else {
	SoField *field = auditorInfo->connection.field;
	field->removeAuditor(this, SoNotRec::FIELD);
	auditorInfo->connection.field = NULL;
    }
    flags.connected = FALSE;
    flags.converted = FALSE;
}
