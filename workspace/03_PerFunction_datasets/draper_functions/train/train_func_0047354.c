cancelRequest(QContactAbstractRequest* req)
{
    if (m_controllerForRequest.contains(req)) {
        RequestController* controller = m_controllerForRequest.value(req);
        if (controller) {


            delete controller;
            m_controllerForRequest.insert(req, 0);
        }
        return true;
    } else {
        return m_engine->cancelRequest(req);
    }
}
