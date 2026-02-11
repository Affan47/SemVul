constructor(QScriptContext *context, QScriptEngine *engine)
	{
		InputDialog *inputDialog = new InputDialog;
		inputDialog->setupConstructorParameters(context, engine, context->argument(0));

		QScriptValueIterator it(context->argument(0));

		while(it.hasNext())
		{
			it.next();

			if(it.name() == "labelText")
				inputDialog->mInputDialog->setLabelText(it.value().toString());
			else if(it.name() == "okButtonText")
				inputDialog->mInputDialog->setOkButtonText(it.value().toString());
			else if(it.name() == "cancelButtonText")
				inputDialog->mInputDialog->setCancelButtonText(it.value().toString());
			else if(it.name() == "textEchoMode")
				inputDialog->mInputDialog->setTextEchoMode(static_cast<QLineEdit::EchoMode>(it.value().toInt32()));
			else if(it.name() == "floatDecimals")
				inputDialog->mInputDialog->setDoubleDecimals(it.value().toInt32());
			else if(it.name() == "integerStep")
				inputDialog->mInputDialog->setIntStep(it.value().toInt32());
			else if(it.name() == "minimum")
				inputDialog->mMinimum = it.value();
			else if(it.name() == "maximum")
				inputDialog->mMaximum = it.value();
			else if(it.name() == "range")
			{
				inputDialog->mMinimum = it.value().property("minimum");
				inputDialog->mMaximum = it.value().property("maximum");
			}
			else if(it.name() == "inputType")
				inputDialog->mInputType = static_cast<InputType>(it.value().toInt32());
			else if(it.name() == "value")
				inputDialog->mValue = it.value();
			else if(it.name() == "items")
				inputDialog->mItems = it.value();
			else if(it.name() == "itemsEditable")
				inputDialog->mInputDialog->setComboBoxEditable(it.value().toBool());
			else if(it.name() == "onClosed")
				inputDialog->mOnClosed = it.value();
			else if(it.name() == "onValueChanged")
				inputDialog->mOnValueChanged = it.value();
		}

		return CodeClass::constructor(inputDialog, context, engine);
	}
