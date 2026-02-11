findBoard(QGraphicsItem* item_)
{

	return item_ ? dynamic_cast<Tagaro::Board*>(item_->topLevelItem()) : 0;
}
