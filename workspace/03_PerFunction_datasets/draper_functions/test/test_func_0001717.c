addChild_impl(Window* wnd)
{
    Window::addChild_impl(wnd);


    d_eventConnections.insert(std::make_pair(wnd,
        wnd->subscribeEvent(Window::EventSized,
            Event::Subscriber(&LayoutContainer::handleChildSized, this))));
    d_eventConnections.insert(std::make_pair(wnd,
        wnd->subscribeEvent(Window::EventMarginChanged,
            Event::Subscriber(&LayoutContainer::handleChildMarginChanged, this))));
}
