loadXPDataIntoLocal(void)
{


	XAP_GtkSignalBlocker b1(  G_OBJECT(m_oAlignList_adj), m_iAlignListSpinID);
	XAP_GtkSignalBlocker b2(  G_OBJECT(m_oIndentAlign_adj), m_iIndentAlignSpinID);

	XAP_GtkSignalBlocker b3(  G_OBJECT(m_wDecimalEntry), m_iDecimalEntryID);
	XAP_GtkSignalBlocker b4(  G_OBJECT(m_wDelimEntry), m_iDelimEntryID );


	m_bDontUpdate = true;

	UT_DEBUGMSG(("loadXP newListType = %d \n",getNewListType()));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(m_wAlignListSpin),getfAlign());
	float indent = getfAlign() + getfIndent();
	gtk_spin_button_set_value(GTK_SPIN_BUTTON( m_wIndentAlignSpin),indent);
	if( (getfIndent() + getfAlign()) < 0.0)
	{
		setfIndent( - getfAlign());
		gtk_spin_button_set_value(GTK_SPIN_BUTTON( m_wIndentAlignSpin), 0.0);

	}


	if(getFont() == "NULL")
	{
		gtk_combo_box_set_active(m_wFontOptions, 0 );
	}
	else
	{
        size_t i = 0;
		for(std::vector<std::string>::const_iterator iter = m_glFonts.begin();
            iter != m_glFonts.end(); ++iter, ++i)
		{
			if(*iter == getFont())
				break;
		}
        if(i < m_glFonts.size())
		{
			gtk_combo_box_set_active(m_wFontOptions, i + 1 );
		}
		else
		{
			gtk_combo_box_set_active(m_wFontOptions, 0 );
		}
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(m_wStartSpin),static_cast<float>(getiStartValue()));

    gtk_entry_set_text( GTK_ENTRY(m_wDecimalEntry), getDecimal().c_str());
	gtk_entry_set_text( GTK_ENTRY(m_wDelimEntry), getDelim().c_str());


	FL_ListType save = getNewListType();
	if(getNewListType() == NOT_A_LIST)
	{
		styleChanged(0);
		setNewListType(save);
		gtk_combo_box_set_active(m_wListTypeBox, 0);
		gtk_combo_box_set_active(m_wListStyleBox, 0);
	}
	else if(IS_BULLETED_LIST_TYPE(getNewListType()) )
	{
		styleChanged(1);
		setNewListType(save);
		gtk_combo_box_set_active(m_wListTypeBox, 1);
		gtk_combo_box_set_active(m_wListStyleBox, (gint) (getNewListType() - BULLETED_LIST));
	}
	else
	{
		styleChanged(2);
	    setNewListType(save);
		gtk_combo_box_set_active(m_wListTypeBox, 2);
		if(getNewListType() < OTHER_NUMBERED_LISTS)
		{
			gtk_combo_box_set_active(m_wListStyleBox, getNewListType());
		}
		else
		{
		    gint iMenu = static_cast<gint>(getNewListType()) - OTHER_NUMBERED_LISTS + BULLETED_LIST -1 ;
			gtk_combo_box_set_active(m_wListStyleBox,iMenu);
		}
	}


	m_bDontUpdate = false;
}
