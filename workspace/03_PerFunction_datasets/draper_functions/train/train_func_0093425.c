connectFrom(SoEngineOutput *engineOutput)


{
    SoFieldContainer	*engineCont = engineOutput->getContainer();

#ifdef DEBUG

    if (engineCont == NULL) {
	SoDebugError::post("SoField::connectFrom",
			   "Can't connect to an engine output "
			   "that is not contained in an engine");
	return FALSE;
    }
#endif


    engineCont->ref();


    disconnect();


    SoType outputType = engineOutput->getConnectionType();
    if (getTypeId() != outputType) {

	SbBool			ret;
	SoFieldConverter	*converter;

	converter = createConverter(outputType);


	if (converter == NULL)
	    ret = FALSE;
	else {
	    converter->ref();


	    SoField *c_input = converter->getInput(outputType);
	    SoEngineOutput *c_output =
		converter->getOutput(getTypeId());
#ifdef DEBUG
	    if (c_input == NULL || c_output == NULL) {
		SoDebugError::post("SoField::connectFrom",
				   "Created converter, but converter"
				   "input or output is NULL");
		return FALSE;
	    }
#endif


	    flags.converted = TRUE;
	    flags.fromEngine = TRUE;

	    c_input->connectFrom(engineOutput);
	    connectFrom(c_output);

	    converter->unref();
	    ret = TRUE;
	}

	engineCont->unrefNoDelete();

	return ret;
    }

    createAuditorInfo();

    flags.connected       = TRUE;


    if (!flags.converted)
	flags.fromEngine      = TRUE;

    auditorInfo->connection.engineOutput = engineOutput;


    engineOutput->addConnection(this);

    if (isConnectionEnabled() && engineOutput->isEnabled()) {


	setDefault(FALSE);


	startNotify();
    }


    engineCont->unrefNoDelete();

    return TRUE;
}
