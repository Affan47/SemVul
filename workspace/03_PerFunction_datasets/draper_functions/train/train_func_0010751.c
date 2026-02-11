transformStringToMatrix(const QString & transform) {


	QList<double> floats = getTransformFloats(transform);

	if (transform.startsWith("translate")) {
		return QMatrix().translate(floats[0], (floats.length() > 1) ? floats[1] : 0);
	}
	else if (transform.startsWith("rotate")) {
		if (floats.length() == 1) {
			return QMatrix().rotate(floats[0]);
		}
		else if (floats.length() == 3) {
			return  QMatrix().translate(-floats[1], -floats[2]) * QMatrix().rotate(floats[0]) * QMatrix().translate(floats[1], floats[2]);
		}
	}
	else if (transform.startsWith("matrix")) {
        return QMatrix(floats[0], floats[1], floats[2], floats[3], floats[4], floats[5]);
	}
	else if (transform.startsWith("scale")) {
		return QMatrix().scale(floats[0], floats[1]);
	}
	else if (transform.startsWith("skewX")) {
		return QMatrix().shear(floats[0], 0);
	}
	else if (transform.startsWith("skewY")) {
		return QMatrix().shear(0, floats[0]);
	}

	return QMatrix();
}
