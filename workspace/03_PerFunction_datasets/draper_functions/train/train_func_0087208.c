forceImmediateUpdateOfAllVisualizations()
{
    foreach (DataContainer *source, d->sources) {
        source->forceImmediateUpdate();
    }
}
