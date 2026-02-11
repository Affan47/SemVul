GLRenderS(SoAction *action, SoNode *node)
{
    SoGLRenderAction *a = (SoGLRenderAction *) action;

    if (! a->abortNow())
	node->GLRender(a);
    else {
	SoCacheElement::invalidate(action->getState());
    }
}
