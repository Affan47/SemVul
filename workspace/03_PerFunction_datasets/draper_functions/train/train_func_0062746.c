Writeout(Aoutfile *f)
{
	f->PutInt(num);
	if (type != -1) f->PutStr(ObjectDefs[type].name);
	else f->PutStr("NO_OBJECT");
	f->PutInt(incomplete);
	f->PutStr(*name);
	if (describe) {
		f->PutStr(*describe);
	} else {
		f->PutStr("none");
	}
	f->PutInt(inner);
	if (Globals->PREVENT_SAIL_THROUGH && !Globals->ALLOW_TRIVIAL_PORTAGE)
		f->PutInt(prevdir);
	else
		f->PutInt(-1);
	f->PutInt(runes);
	f->PutInt(units.Num());
	forlist ((&units))
		((Unit *) elem)->Writeout(f);
	WriteoutFleet(f);
}
