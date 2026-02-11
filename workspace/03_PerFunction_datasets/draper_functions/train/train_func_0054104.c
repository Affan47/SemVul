onChildRemoved(WindowEventArgs& e)
{
    Window::onChildRemoved(e);


    ConnectionTracker::iterator conn;
    while ((conn = d_eventConnections.find(e.window)) != d_eventConnections.end())
    {
        conn->second->disconnect();
        d_eventConnections.erase(conn);
    }


    if (!d_destructionStarted)
    {
        WindowEventArgs args(this);
        onContentChanged(args);
    }
}
