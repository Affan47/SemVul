checkDelayInterval(Type t)
{
	interval i = t->getInterval();
	if (i.valid && i.lo >= 0) {
		return int(i.hi+0.5);
	} else {

		return -1;
	}
}
