maxCost(EventTypeMapping* mapping, FixString & s)
{
    if (!mapping) return;
    s.stripSpaces();
    if (s.isEmpty()) return;
    reserve(mapping->set()->realCount());

    SubCost v;
    if (mapping->isIdentity()) {
	int i = 0;
	while(i<mapping->count()) {
	    if (!s.stripUInt64(v)) break;
	    if (i<_count) {
	      if (v>_cost[i]) _cost[i] = v;
	    }
	    else
		_cost[i] = v;
	    i++;
	}
	if (i > _count) _count = i;
    }
    else {
	int i = 0, maxIndex = 0, index;
	while(1) {
	    if (!s.stripUInt64(v)) break;
	    index = mapping->realIndex(i);
	    if (maxIndex<index) maxIndex=index;
	    if (index == ProfileCostArray::InvalidIndex) break;
	    if (index<_count) {
	      if (v>_cost[index]) _cost[index] = v;
	    }
	    else
		_cost[index] = v;
	    i++;
	}
	if (maxIndex >= _count) {


	    for(i=mapping->nextUnused(_count-1); i<=maxIndex; i=mapping->nextUnused(i))
		_cost[i] = 0;
	    _count = maxIndex+1;
	}
    }

    Q_ASSERT(_count <= _allocCount);
    invalidate();

#if TRACE_DEBUG
    _dirty = false;
    qDebug("%s\n now %s", qPrintable( fullName() ),
	   qPrintable(ProfileCostArray::costString(0)));
    _dirty = true;
#endif
}
