EditLabel(long item, wxClassInfo* textControlClass)
{
    wxCHECK_MSG( (item >= 0) && ((size_t)item < GetItemCount()), NULL,
                 wxT("wrong index in wxGenericListCtrl::EditLabel()") );

    wxASSERT_MSG( textControlClass->IsKindOf(CLASSINFO(wxTextCtrl)),
                 wxT("EditLabel() needs a text control") );

    size_t itemEdit = (size_t)item;

    wxListEvent le( wxEVT_COMMAND_LIST_BEGIN_LABEL_EDIT, GetParent()->GetId() );
    le.SetEventObject( GetParent() );
    le.m_itemIndex = item;
    wxListLineData *data = GetLine(itemEdit);
    wxCHECK_MSG( data, NULL, _T("invalid index in EditLabel()") );
    data->GetItem( 0, le.m_item );

    if ( GetParent()->GetEventHandler()->ProcessEvent( le ) && !le.IsAllowed() )
    {

        return NULL;
    }


    if ( m_dirty )
    {
        wxSafeYield();


        if ( (size_t)item >= GetItemCount() )
            return NULL;
    }

    wxTextCtrl * const text = (wxTextCtrl *)textControlClass->CreateObject();
    m_textctrlWrapper = new wxListTextCtrlWrapper(this, text, item);
    return m_textctrlWrapper->GetText();
}
