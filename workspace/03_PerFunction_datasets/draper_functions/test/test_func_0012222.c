consolePrint(const QString &text, ActionTools::ConsoleWidget::Type type)
	{
		ActionTools::ActionInstance *currentAction = mScript->actionAt(currentActionIndex());
		qint64 currentActionRuntimeId = -1;
		if(currentAction)
			currentActionRuntimeId = currentAction->runtimeId();

		consoleWidget()->addUserLine(text,
									   currentActionRuntimeId,
									   mScriptEngine->currentContext()->engine()->property("currentParameter").toString(),
									   mScriptEngine->currentContext()->engine()->property("currentSubParameter").toString(),
									   mScriptAgent->currentLine(),
									   mScriptAgent->currentColumn(),
									   mScriptEngine->currentContext()->backtrace(),
									   type);
	}
