value ()
{
	qreal zero = scene ()->height () / 2.0;
	qreal ret = 0.0;
	qreal p = pos ().y () + 3;
	if (p < zero) {
		ret = 20.0 - (20.0 * (p / zero));
	} else {

		ret = -(20.0 * ((p - zero) / zero));
	}

	return ret;
}
