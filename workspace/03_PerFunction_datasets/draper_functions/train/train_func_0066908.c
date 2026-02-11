copy(Counters & from, Counters & to, docstring const & match)
{
	CounterList::iterator it = counterList_.begin();
	CounterList::iterator end = counterList_.end();
	for (; it != end; ++it) {
		if (it->first.find(match) != string::npos || match == "") {
			to.set(it->first, from.value(it->first));
		}
	}
}
