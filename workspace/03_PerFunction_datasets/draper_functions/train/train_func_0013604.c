slot_edit()
{
	int item = _listBox->currentRow();
	if( item != -1 ) {
		DialogCreatureAnimation dialog;
		dialog.setModifType( ( (CreatureAnimationItem*)(_listBox->item( item ) ) )->getModifType() );
		dialog.setFirst( ( (CreatureAnimationItem*)(_listBox->item( item ) ) )->getFirst() );
		dialog.setLast( ( (CreatureAnimationItem*)(_listBox->item( item ) ) )->getLast() );
		if( dialog.exec() ) {
			CreatureAnimationType ElementaryType = dialog.getModifType();
			uint first = dialog.getFirst();
			int last = dialog.getLast();
			CreatureAnimationItem * action = (CreatureAnimationItem*) _listBox->item( item );
			action->setModifType( ElementaryType );
			action->setFirst( first );
			action->setLast( last );
		}
	}
}
