Dump(std::ostream &os) const
{
	ios_format_state state(os);

	static const char *PriorityName[] = {
		N_("High"),
		N_("Normal"),
		N_("Low")
	};
	static const char *StatusName[] = {
		N_("Not Started"),
		N_("In Progress"),
		N_("Completed"),
		N_("Waiting"),
		N_("Deferred")
	};
	static const char *AlarmTypeName[] = {
		N_("None"),
		N_("By Date"),
		N_("Relative")
	};

	os << _("Task entry: ") << "0x" << setbase(16) << RecordId
	   << " (" << (unsigned int)RecType << ")\n";


	for(	const FieldLink<Task> *b = TaskFieldLinks;
		b->type != TSKFC_END;
		b++ )
	{
		if( b->strMember ) {
			const std::string &s = this->*(b->strMember);
			if( s.size() )
				os << "   " << gettext(b->name) << ": " << Cr2LfWrapper(s) << "\n";
		}
		else if( b->timeMember ) {
			TimeT t = this->*(b->timeMember);
			if( t.IsValid() )
				os << "   " << gettext(b->name) << ": " << t << "\n";
		}
	}

	os << _("   Priority: ") << gettext(PriorityName[PriorityFlag]) << "\n";
	os << _("   Status: ") << gettext(StatusName[StatusFlag]) << "\n";
	if( AlarmType ) {
		os << _("   Alarm Type: ") << gettext(AlarmTypeName[AlarmType]) << "\n";
	}
	if( TimeZoneValid )
		os << _("   Time Zone: ") << gettext(GetStaticTimeZone(TimeZoneCode)->Name) << "\n";


	RecurBase::Dump(os);

	if( Categories.size() ) {
		string display;
		Categories.CategoryList2Str(display);
		os << _("   Categories: ") << display << "\n";
	}

	os << Unknowns;
	os << "\n\n";
}
