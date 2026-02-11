takeFromWidget(const CLAM::DynamicType & object, unsigned attribute, QWidget * editorWidget)
	{
		QCheckBox * input = dynamic_cast<QCheckBox*>(editorWidget);
		bool & value = *(bool *)object.GetAttributeAsVoidPtr(attribute);
		value = input->isChecked();
	}
}
