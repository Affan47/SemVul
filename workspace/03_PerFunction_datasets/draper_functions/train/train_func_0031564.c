countWriteRefs(SoOutput *out) const


{
    if (! isConnected())
	return;


    if (flags.fromEngine || flags.converted) {


	SoEngine *container =
	    auditorInfo->connection.engineOutput->getContainer();
	if (container != NULL)
	    container->addWriteReference(out);
    }


    else {
	SoField	*field;
	getConnectedField(field);
	SoFieldContainer *container = field->getContainer();
	if (container != NULL)
	    container->addWriteReference(out, TRUE);
    }
}
