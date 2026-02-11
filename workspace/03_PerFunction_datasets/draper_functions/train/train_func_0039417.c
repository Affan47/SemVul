dispatchUIEvent(int _id, int detail)
{
    assert (!( (_id != EventImpl::DOMFOCUSIN_EVENT &&
        _id != EventImpl::DOMFOCUSOUT_EVENT &&
                _id != EventImpl::DOMACTIVATE_EVENT)));

    bool cancelable = false;
    if (_id == EventImpl::DOMACTIVATE_EVENT)
        cancelable = true;

    int exceptioncode = 0;
    UIEventImpl* const evt = new UIEventImpl(static_cast<EventImpl::EventId>(_id),true,
                                       cancelable, document()->defaultView(), detail);
    evt->ref();
    dispatchEvent(evt,exceptioncode,true);
    evt->deref();
}
