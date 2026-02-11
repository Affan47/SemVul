doAction(SoAction *action)


{
    if (! value.isIgnored() &&
	!SoOverrideElement::getMaterialBindingOverride(action->getState())) {
	if (isOverride()) {
	    SoOverrideElement::
		setMaterialBindingOverride(action->getState(), this, TRUE);
	}
	SoMaterialBindingElement::set(action->getState(),
		(SoMaterialBindingElement::Binding)value.getValue());
    }
}
