landmarkFetchStateChanged(QLandmarkAbstractRequest::State newState)
{
    if (newState == QLandmarkAbstractRequest::FinishedState) {
        QLandmarkFetchRequest *req = qobject_cast<QLandmarkFetchRequest*>(sender());
        if (req->error() == QLandmarkManager::NoError) {

            QList<QLandmark> landmarks = req->landmarks();
            for (int i = 0; i < landmarks.size(); ++i)
                addPlace(landmarks.at(i));

            fetchRequests.removeAll(req);
            delete req;

            if (!searchReply && (fetchRequests.size() == 0))
                emit finished();
        } else {

            emit error(QGeoSearchReply::CombinationError, req->errorString());

            delete searchReply;
            searchReply = 0;
            qDeleteAll(fetchRequests);
            fetchRequests.clear();
        }
    }
}
