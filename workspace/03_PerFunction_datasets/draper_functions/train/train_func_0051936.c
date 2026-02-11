rw_recurseFindLayout(QLayout *lo, QWidget *w)
{

	QLayoutIterator it = lo->iterator();
	for(QLayoutItem *i; (i = it.current()); ++it) {

		QLayout *slo = i->layout();
		if(slo) {
			QLayout *tlo = rw_recurseFindLayout(slo, w);
			if(tlo)
				return tlo;
		}
		else if(i->widget() == w)
			return lo;
	}
	return 0;
}
