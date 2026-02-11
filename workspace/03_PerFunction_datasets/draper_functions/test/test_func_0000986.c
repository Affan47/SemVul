pause(QScriptContext *context, QScriptEngine *engine)
	{
		Q_UNUSED(engine)

		ActionTools::CrossPlatform::sleep(context->argument(0).toInt32());

		return context->thisObject();
	}
