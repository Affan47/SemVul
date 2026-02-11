checkSyntax()
	{
		if(mCode)
		{
			QScriptSyntaxCheckResult result = QScriptEngine::checkSyntax(toPlainText());
			if(result.state() != QScriptSyntaxCheckResult::Valid)
			{
				setCurrentLine(result.errorLineNumber());
				setCurrentColumn(result.errorColumnNumber());

				mLastSyntaxError = result.errorMessage();

				return false;
			}
		}

		return true;
	}
