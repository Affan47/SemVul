PollHandler(SocketEvent evt)
{
    int id = evt.conn->GetConnectionId();
    if (conn_[id] == NULL) conn_[id] = new HttpClient(DefaultHttpRequestHandler);

    switch (evt.code)
    {
        case SC_READ:
        case SC_WRITE:
            {
                conn_[id]->ProcessEvent(evt);
            }
            break;
        case SC_ACCEPTED:
            {
                static int co = 0;
                ++co;
                slog(LOG_INFO, "accept(%d)", co);
                conn_[id]->ResetClient(evt.conn);
            }
            break;
        case SC_FAIL_CONN:
            {
                evt.conn->CloseConnection();
            }
            break;
        case SC_ERROR:
            {
            }
            break;
        default:
            {
            }
            break;
    }
}
