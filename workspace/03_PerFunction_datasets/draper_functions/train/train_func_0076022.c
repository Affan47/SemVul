editorWidget(const CLAM::DynamicType & object, unsigned attribute)
	{
		const CLAM::Enum & value = *(CLAM::Enum *)object.GetAttributeAsVoidPtr(attribute);
		QComboBox * input = new QComboBox( false);
		const CLAM::Enum::tEnumValue * mapping = value.GetSymbolMap();
		for (unsigned i = 0; mapping[i].name; i++) {
			input->addItem( mapping[i].name );
			if (mapping[i].value==value.GetValue()) input->setCurrentIndex(i);
		}
		return input;
	}
