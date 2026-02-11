httpServerDiscardRequests(HTTPServerPtr server)
{
    HTTPRequestPtr request;
    while(server->request && !server->request->request) {
        request = server->request;
        server->request = request->next;
        request->next = NULL;
        if(server->request == NULL)
            server->request_last = NULL;
        request->object->flags &= ~(OBJECT_INPROGRESS | OBJECT_VALIDATING);
        releaseNotifyObject(request->object);
        request->object = NULL;
        httpDestroyRequest(request);
    }
}
