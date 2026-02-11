updateDefinitionRemoveRequest(QContactDetailDefinitionRemoveRequest* req, QContactManager::Error error, const QMap<int, QContactManager::Error>& errorMap, QContactAbstractRequest::State newState)
{
    if (req) {
        QWeakPointer<QContactDetailDefinitionRemoveRequest> ireq(req);
        QContactDetailDefinitionRemoveRequestPrivate* rd = static_cast<QContactDetailDefinitionRemoveRequestPrivate*>(req->d_ptr);
        QMutexLocker ml(&rd->m_mutex);
        bool emitState = rd->m_state != newState;
        rd->m_errors = errorMap;
        rd->m_error = error;
        rd->m_state = newState;
        ml.unlock();
        emit ireq.data()->resultsAvailable();
        if (emitState && ireq)
            emit ireq.data()->stateChanged(newState);
    }
}
