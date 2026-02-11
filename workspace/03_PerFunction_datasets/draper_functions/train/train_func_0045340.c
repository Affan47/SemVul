doAction(SoAction *action)


{

    if (! on.isIgnored() && on.getValue() == FALSE)
	return;

    if (! plane.isIgnored()) {
	SoClipPlaneElement::add(action->getState(), this, plane.getValue());
    }
}
