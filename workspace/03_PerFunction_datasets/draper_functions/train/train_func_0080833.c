lookupCounter(const DOMString& counter) const
{
    QHash<DOMString,khtml::CounterNode*>* counters = document()->counters(this);
    return counters ? counters->value(counter) : 0;
}
