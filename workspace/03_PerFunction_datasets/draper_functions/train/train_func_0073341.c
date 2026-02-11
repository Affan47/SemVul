doAction(SoAction *action)


{
    SoState	*state = action->getState();

    if (! model.isIgnored()
	&& ! SoOverrideElement::getLightModelOverride(state)) {
	if (isOverride()) {
	    SoOverrideElement::setLightModelOverride(state, this, TRUE);
	}

	SoLazyElement::LightModel lt =
	    (SoLazyElement::LightModel) model.getValue();

	SoLazyElement::setLightModel(state, lt);
    }
}
