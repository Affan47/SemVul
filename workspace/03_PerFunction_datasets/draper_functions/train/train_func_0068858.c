removeLandmark(const QLandmark &landmark)
{
    Q_D(QLandmarkManager);

    if (!d->engine) {
        return false;
    }

    d->errorCode = QLandmarkManager::NoError;
    d->errorString = "";
    d->errorMap.clear();

    return d->engine->removeLandmark(landmark.landmarkId(),
                                     &(d->errorCode),
                                     &(d->errorString));

}
