buildTree()
{
	_list->clear();
	if( _condition ) {
		QuestConditionItem * item = new QuestConditionItem( _list );
		item->setExpanded( true );
		item->setCondition( _condition );
		if( _condition->getType() == QuestCondition::COMPOSITE ) {
			QuestConditionComposite * composite = ( QuestConditionComposite * ) _condition;
			uint nb = composite->getConditionNumber();
			for( uint i = 0; i < nb; ++i ) {
				buildSubTree( item, composite->getCondition( i ) );
			}
		}
	}
}
