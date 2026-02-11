move(QScriptContext *context, QScriptEngine *engine)
	{
		QString source, destination;
		bool noErrorDialog, noConfirmDialog, noProgressDialog, allowUndo, createDestinationDirectory;

		if(getParameters(source, destination, context->argument(2), noErrorDialog, noConfirmDialog, noProgressDialog, allowUndo, createDestinationDirectory, context, engine))
			movePrivate(source, destination, noErrorDialog, noConfirmDialog, noProgressDialog, allowUndo, createDestinationDirectory, context, engine);

		return engine->undefinedValue();
	}
