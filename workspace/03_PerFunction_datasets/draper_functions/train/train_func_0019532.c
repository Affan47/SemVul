save(ActionInstance *actionInstance)
	{
		actionInstance->setSubParameter(name().original(), "value", mColorEdit->isCode(), mColorEdit->text());
	}
