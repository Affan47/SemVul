parseAttribute(AttributeImpl *attr)
{
    switch(attr->id())
    {
    case ATTR_ACTION:
        break;
    case ATTR_TARGET:
        m_target = attr->value();
        break;
    case ATTR_METHOD:
        m_post = ( strcasecmp( attr->value(), "post" ) == 0 );
        break;
    case ATTR_ENCTYPE:
        setEnctype( attr->value() );
        break;
    case ATTR_ACCEPT_CHARSET:


        m_acceptcharset = attr->value();
        break;
    case ATTR_ACCEPT:

        break;
    case ATTR_AUTOCOMPLETE:
        m_autocomplete = strcasecmp( attr->value(), "off" );
        break;
    case ATTR_ONSUBMIT:
        setHTMLEventListener(EventImpl::SUBMIT_EVENT,
	    document()->createHTMLEventListener(attr->value().string(), "onsubmit", this));
        break;
    case ATTR_ONRESET:
        setHTMLEventListener(EventImpl::RESET_EVENT,
	    document()->createHTMLEventListener(attr->value().string(), "onreset", this));
        break;
    case ATTR_NAME:
        if (inDocument() && m_name != attr->value()) {
            document()->underDocNamedCache().remove(m_name,        this);
            document()->underDocNamedCache().add   (attr->value(), this);
        }
        m_name = attr->value();

    default:
        HTMLElementImpl::parseAttribute(attr);
    }
}
