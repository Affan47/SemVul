allowEquipotentialOverlaps(QGraphicsItem * item, QList<Tile *> & alreadyTiled)
{
	bool collected = false;
	QList<ConnectorItem *> equipotential;
	Wire * w = dynamic_cast<Wire *>(item);
	if (w) {
		equipotential.append(w->connector0());
	}
	else {
		ConnectorItem * ci = dynamic_cast<ConnectorItem *>(item);
		equipotential.append(ci);
	}

	foreach (Tile * intersectingTile, alreadyTiled) {
		QGraphicsItem * bodyItem = TiGetBody(intersectingTile);
		ConnectorItem * ci = dynamic_cast<ConnectorItem *>(bodyItem);
		if (ci != NULL) {
			if (!collected) {
				ConnectorItem::collectEqualPotential(equipotential, false, ViewGeometry::NoFlag);
				collected = true;
			}
			if (!equipotential.contains(ci)) {


				return false;
			}
		}
		else {
			Wire * w = dynamic_cast<Wire *>(bodyItem);
			if (w == NULL) return false;

			if (!collected) {
				ConnectorItem::collectEqualPotential(equipotential, false, ViewGeometry::NoFlag);
				collected = true;
			}

			if (!equipotential.contains(w->connector0())) {


				return false;
			}
		}
	}

	return true;

}
