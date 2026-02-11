GLRender(SoGLRenderAction *action)


{

    if (! whatToReset.isIgnored() && (whatToReset.getValue() & TRANSFORM))
	SoGLModelMatrixElement::makeIdentity(action->getState(), this);
}
