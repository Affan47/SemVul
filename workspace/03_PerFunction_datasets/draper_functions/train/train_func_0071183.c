simple_action(Packet *p)
{
    if (_action == ACT_NOW)
	p->timestamp_anno().assign_now();
    else if (_action == ACT_TIME)
	p->timestamp_anno() = _tv;
    else if (_action == ACT_FIRST_NOW)
	FIRST_TIMESTAMP_ANNO(p).assign_now();
    else
	FIRST_TIMESTAMP_ANNO(p) = _tv;
    return p;
}
