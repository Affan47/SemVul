AreAllChildrenSpecified( wxVariant* pendingList ) const
{
    unsigned int i;

    const wxVariantList* pList = NULL;
    wxVariantList::const_iterator node;

    if ( pendingList )
    {
        pList = &pendingList->GetList();
        node = pList->begin();
    }

    for ( i=0; i<GetChildCount(); i++ )
    {
        wxPGProperty* child = Item(i);
        const wxVariant* listValue = NULL;
        wxVariant value;

        if ( pendingList )
        {
            const wxString& childName = child->GetBaseName();

            for ( ; node != pList->end(); node++ )
            {
                const wxVariant& item = *((const wxVariant*)*node);
                if ( item.GetName() == childName )
                {
                    listValue = &item;
                    value = item;
                    break;
                }
            }
        }

        if ( !listValue )
            value = child->GetValue();

        if ( value.IsNull() )
            return false;


        if ( child->GetChildCount() )
        {
            const wxVariant* childList = NULL;

            if ( listValue && wxPGIsVariantType(*listValue, list) )
                childList = listValue;

            if ( !child->AreAllChildrenSpecified((wxVariant*)childList) )
                return false;
        }
    }

    return true;
}
