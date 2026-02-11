Prev()
{
    wxPGProperty* property = m_property;
    if ( !property )
        return;

    wxPGProperty* parent = property->GetParent();
    wxASSERT( parent );
    unsigned int index = property->GetIndexInParent();

    if ( index > 0 )
    {

        index--;

        property = parent->Item(index);


        if ( property->GetChildCount() &&
             wxPG_ITERATOR_PARENTEXMASK_TEST(property, m_parentExMask) )
        {

            property = property->Last();
        }
    }
    else
    {

        if ( parent == m_baseParent )
        {
            m_property = NULL;
            return;
        }
        else
        {
            property = parent;
        }
    }

    m_property = property;


    if ( property->GetFlags() & m_itemExMask )
        Prev();
}
