pieceAt(const QPointF& pos) const
{
	foreach (QGraphicsItem* item, items(pos))
	{
		GraphicsPiece* piece = qgraphicsitem_cast<GraphicsPiece*>(item);
		if (piece != 0)
			return piece;
	}

	return 0;
}
