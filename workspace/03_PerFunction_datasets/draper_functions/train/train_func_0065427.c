painterPathCommandSlot(QChar command, bool relative, QList<double> & args, void * userData) {

	Q_UNUSED(relative);
	Q_UNUSED(command)

	PathUserData * pathUserData = (PathUserData *) userData;

	double dx, dy;
	for (int i = 0; i < args.count(); i += 2) {
		dx = args[i];
		dy = args[i + 1];
		if (i == 0) {
			pathUserData->painterPath->moveTo(dx, dy);
		}
		else {
			pathUserData->painterPath->lineTo(dx, dy);
		}
	}
	pathUserData->painterPath->closeSubpath();


}
