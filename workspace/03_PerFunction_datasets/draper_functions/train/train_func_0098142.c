internalUpdateSource(DataContainer *source)
{
    if (minPollingInterval > 0 &&
        source->timeSinceLastUpdate() < (uint)minPollingInterval) {


        source->setNeedsUpdate();
        return;
    }

    if (q->updateSourceEvent(source->objectName())) {

        q->scheduleSourcesUpdated();
    }


}
