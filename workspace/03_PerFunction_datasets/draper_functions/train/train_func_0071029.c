propertyEvent(XPropertyEvent &event) {
    ClientHandlerList::iterator it = m_clienthandlers.begin();
    ClientHandlerList::iterator it_end = m_clienthandlers.end();
    for (; it != it_end; ++it) {
        (*it)->propertyNotify(*this, event);
    }
    updateWindowHints(event.window);
}
