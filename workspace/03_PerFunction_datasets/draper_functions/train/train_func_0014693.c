compare(Q3ListViewItem *lvi, int, bool) const
{
	ContactViewItem *i = (ContactViewItem *)lvi;
	int ret = 0;

	if(type_ == Contact) {

		if(i->type() == Group)
			ret = -1;
		else {
			if ( PsiOptions::instance()->getOption("options.ui.contactlist.contact-sort-style").toString() == "status" ) {
				ret = rankStatus(d->status) - rankStatus(i->status());
				if(ret == 0)
					ret = text(0).lower().localeAwareCompare(i->text(0).lower());
			}
			else {
				ret = text(0).lower().localeAwareCompare(i->text(0).lower());
			}
		}
	}
	else if(type_ == Group || type_ == Profile) {

		if(i->type() == Contact)
			ret = 1;
		else if(i->type() == Group) {
			if ( PsiOptions::instance()->getOption("options.ui.contactlist.group-sort-style").toString() == "rank") {
				int ourRank   = d->groupData().rank;
				int theirRank = i->d->groupData().rank;

				ret = ourRank - theirRank;
			}
			else {
				ret = rankGroup(d->groupType) - rankGroup(i->groupType());
				if(ret == 0)
					ret = text(0).lower().localeAwareCompare(i->text(0).lower());
			}
		}
		else if(i->type() == Profile) {
			if ( PsiOptions::instance()->getOption("options.ui.contactlist.account-sort-style").toString() == "rank" ) {
				int ourRank = d->groupData().rank;
				int theirRank = i->d->groupData().rank;

				ret = ourRank - theirRank;
			}
			else
				ret = text(0).lower().localeAwareCompare(i->text(0).lower());
		}
	}

	return ret;
}
