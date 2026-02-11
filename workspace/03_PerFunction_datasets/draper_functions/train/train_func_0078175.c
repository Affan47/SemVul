constructor(QScriptContext *context, QScriptEngine *engine)
	{
		MessageBox *messageBox = new MessageBox;
		messageBox->setupConstructorParameters(context, engine, context->argument(0));

		QScriptValueIterator it(context->argument(0));

		while(it.hasNext())
		{
			it.next();

			if(it.name() == "text")
				messageBox->mMessageBox->setText(it.value().toString());
			else if(it.name() == "detailedText")
				messageBox->mMessageBox->setDetailedText(it.value().toString());
			else if(it.name() == "informativeText")
				messageBox->mMessageBox->setInformativeText(it.value().toString());
			else if(it.name() == "buttons")
				messageBox->mMessageBox->setStandardButtons(static_cast<QMessageBox::StandardButton>(it.value().toInt32()));
			else if(it.name() == "icon")
				messageBox->mMessageBox->setIcon(static_cast<QMessageBox::Icon>(it.value().toInt32()));
			else if(it.name() == "defaultButton")
				messageBox->mMessageBox->setDefaultButton(static_cast<QMessageBox::StandardButton>(it.value().toInt32()));
			else if(it.name() == "escapeButton")
				messageBox->mMessageBox->setEscapeButton(static_cast<QMessageBox::StandardButton>(it.value().toInt32()));
			else if(it.name() == "onClosed")
				messageBox->mOnClosed = it.value();
		}

		return CodeClass::constructor(messageBox, context, engine);
	}
