createPopupMenu( const QPoint &pos )
{
    enum { IdUndo, IdRedo, IdSep1, IdCut, IdCopy, IdPaste, IdClear, IdSep2, IdSelectAll };

    Q3PopupMenu *menu = Q3TextEdit::createPopupMenu( pos );

    if ( isReadOnly() )
      menu->changeItem( menu->idAt(0), KIcon("edit-copy"), menu->text( menu->idAt(0) ) );
    else {
      int id = menu->idAt(0);
      menu->changeItem( id - IdUndo, KIcon("edit-undo"), menu->text( id - IdUndo) );
      menu->changeItem( id - IdRedo, KIcon("edit-redo"), menu->text( id - IdRedo) );
      menu->changeItem( id - IdCut, KIcon("edit-cut"), menu->text( id - IdCut) );
      menu->changeItem( id - IdCopy, KIcon("edit-copy"), menu->text( id - IdCopy) );
      menu->changeItem( id - IdPaste, KIcon("edit-paste"), menu->text( id - IdPaste) );
      menu->changeItem( id - IdClear, KIcon("edit-clear"), menu->text( id - IdClear) );

        menu->insertSeparator();
        id = menu->insertItem( KIcon( "tools-check-spelling" ), i18n( "Check Spelling..." ),
                                   this, SLOT(checkSpelling()) );

        if( text().isEmpty() )
            menu->setItemEnabled( id, false );

        id = menu->insertItem( i18n( "Auto Spell Check" ),
                               this, SLOT(toggleAutoSpellCheck()) );
        menu->setItemChecked(id, d->checkSpellingEnabled);
	menu->insertSeparator();
	id=menu->insertItem(i18n("Allow Tabulations"),this,SLOT(slotAllowTab()));
	menu->setItemChecked(id, !tabChangesFocus());
    }

    return menu;
}
