toOptions(OptionsTree *o, QString base)
{
	o->removeOption(base, true);
	foreach(VarListItem item, *this) {
		QString ibase = o->mapPut(base, item.key());
		o->setOption(ibase + ".data", item.data());
	}
}
