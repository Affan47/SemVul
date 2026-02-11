setWordType(KasumiWordType *aType)
{
    if(aType->equal(mWordType))
	return;

    mWordType = aType;

    for(size_t i=0;i<EventListeners.size();i++){
	EventListeners[i]->changedWordType(this);
    }
}
