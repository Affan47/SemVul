checkBoards(QDomElement & board, QHash<QString, QString> & fzzFilePaths)
{
	while (!board.isNull()) {
		QString boardname = board.attribute("name");

		bool ok;
		int optional = board.attribute("maxOptionalCount", "").toInt(&ok);
		if (!ok) {
			writePanelizerOutput(QString("maxOptionalCount for board '%1' not an integer: '%2'").arg(boardname).arg(board.attribute("maxOptionalCount")));
			return false;
		}

		int optionalPriority = board.attribute("optionalPriority", "").toInt(&ok);
        Q_UNUSED(optionalPriority);
		if (!ok) {
			writePanelizerOutput(QString("optionalPriority for board '%1' not an integer: '%2'").arg(boardname).arg(board.attribute("optionalPriority")));
			return false;
		}

		int required = board.attribute("requiredCount", "").toInt(&ok);
		if (!ok) {
			writePanelizerOutput(QString("required for board '%1' not an integer: '%2'").arg(boardname).arg(board.attribute("maxOptionalCount")));
			return false;
		}

        if (optional > 0 || required> 0) {
		    QString path = fzzFilePaths.value(boardname, "");
		    if (path.isEmpty()) {
			    writePanelizerOutput(QString("File for board '%1' not found in search paths").arg(boardname));
			    return false;
		    }
        }
        else {
            writePanelizerOutput(QString("skipping board '%1'").arg(boardname));
        }

		board = board.nextSiblingElement("board");
	}

	return true;
}
