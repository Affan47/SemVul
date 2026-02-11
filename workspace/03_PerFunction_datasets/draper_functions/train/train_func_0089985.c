killScreenItem(ScreenItem *del)
{
	EnemyAircraft *enemy;
	switch(del->itemType())
	{
		case ScreenItem::ItemEnemy:
			enemy = (EnemyAircraft*)del;
			enemy->back = 0;
			enemy->next = deadPool[enemy->type]->next;
			deadPool[enemy->type]->next = enemy;
			break;
		default:
			delete del;
			break;
	}
}
