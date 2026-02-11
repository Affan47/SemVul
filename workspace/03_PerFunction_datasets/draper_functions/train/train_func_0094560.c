detach()
{
    if(attached())

        document()->dispatchHTMLEvent(EventImpl::UNLOAD_EVENT,false,false);

    HTMLElementImpl::detach();
}
