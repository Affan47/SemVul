slotSelected(int index)
{
    if ( m_ignoreSelectEvents ) return;

    KHTMLAssert( !m_useListBox );

    const QVector<HTMLGenericFormElementImpl*> listItems = element()->listItems();
    if(index >= 0 && index < int(listItems.size()))
    {
        bool found = ( listItems[index]->id() == ID_OPTION );

        if ( !found ) {

            while ( index < listItems.size() ) {
                if ( listItems[index]->id() == ID_OPTION ) {
                    found = true;
                    break;
                }
                ++index;
            }

            if ( !found ) {
                while ( index >= 0 ) {
                    if ( listItems[index]->id() == ID_OPTION ) {
                        found = true;
                        break;
                    }
                    --index;
                }
            }
        }

        if ( found ) {
            bool changed = false;

            for ( int i = 0; i < listItems.size(); ++i )
                if ( listItems[i]->id() == ID_OPTION && i !=  index )
                {
                    HTMLOptionElementImpl* opt = static_cast<HTMLOptionElementImpl*>( listItems[i] );
                    changed |= (opt->m_selected == true);
                    opt->m_selected = false;
                }

            HTMLOptionElementImpl* opt = static_cast<HTMLOptionElementImpl*>(listItems[index]);
            changed |= (opt->m_selected == false);
            opt->m_selected = true;

            if ( index != static_cast<ComboBoxWidget*>( m_widget )->currentIndex() )
                static_cast<ComboBoxWidget*>( m_widget )->setCurrentIndex( index );


            if ( changed )
            {
                ref();
                element()->onChange();
                deref();
            }
        }
    }
}
