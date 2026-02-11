viewportDimensionsChanged(Viewport* viewport)
{
    size_t count = mInstances.size();
    for (size_t i = 0; i < count; ++i)
    {
        mInstances[i]->notifyResized();
    }
}
