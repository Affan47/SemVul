createTrackGroups() {
    mGroups.clear();
    mParents.clear();
    if (mEvents.empty())
    {
        return;
    }
    int trackId = mEvents.first().trackId();

    mGroups << EventModel::Group(Track::retrieveTrackName(trackId), 0);
    int nextTrackId = trackId;

    for (int i=0; i<mEvents.count(); i++)
    {
        trackId = mEvents.at(i).trackId();
        if (nextTrackId != trackId)
        {
            mGroups.last().mChildCount = i - mGroups.last().mFirstEventIndex;
            mGroups << EventModel::Group(Track::retrieveTrackName(trackId), i);
            nextTrackId = trackId;
        }

        mParents[mEvents.at(i).id()] = mGroups.count() - 1;
    }
    mGroups.last().mChildCount = mEvents.count() - mGroups.last().mFirstEventIndex;
}
