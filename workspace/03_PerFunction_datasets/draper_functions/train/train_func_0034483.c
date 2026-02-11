parseAttribute(AttributeImpl *attr)
{
    switch(attr->id())
    {
    case ATTR_VALUE:
        if(m_render && m_render->isListItem() && m_render->style()->display() == LIST_ITEM)
            static_cast<RenderListItem*>(m_render)->setValue(attr->value().toInt());
        break;
    case ATTR_TYPE:
        if ( strcmp( attr->value(), "a" ) == 0 )
            addCSSProperty(CSS_PROP_LIST_STYLE_TYPE, CSS_VAL_LOWER_ALPHA);
        else if ( strcmp( attr->value(), "A" ) == 0 )
            addCSSProperty(CSS_PROP_LIST_STYLE_TYPE, CSS_VAL_UPPER_ALPHA);
        else if ( strcmp( attr->value(), "i" ) == 0 )
            addCSSProperty(CSS_PROP_LIST_STYLE_TYPE, CSS_VAL_LOWER_ROMAN);
        else if ( strcmp( attr->value(), "I" ) == 0 )
            addCSSProperty(CSS_PROP_LIST_STYLE_TYPE, CSS_VAL_UPPER_ROMAN);
        else if ( strcmp( attr->value(), "1" ) == 0 )
            addCSSProperty(CSS_PROP_LIST_STYLE_TYPE, CSS_VAL_DECIMAL);
        else
            addCSSProperty(CSS_PROP_LIST_STYLE_TYPE, attr->value());
        break;
    default:
        HTMLElementImpl::parseAttribute(attr);
    }
}
