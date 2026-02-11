buildEditors(Script *script, QWidget *parent)
	{
		ParameterDefinition::buildEditors(script, parent);

		mSpinBox = new CodeSpinBox(parent);

		mSpinBox->setPrefix(mPrefix);
		mSpinBox->setSuffix(mSuffix);
		mSpinBox->setMaximum(mMaximum);
		mSpinBox->setMinimum(mMinimum);
		mSpinBox->setSingleStep(mSingleStep);

		addEditor(mSpinBox);
	}
