itemDoubleclicked (Q3ListViewItem *item)
{
	DiscoListItem *it = (DiscoListItem *)item;
	if ( !it )
		return;

	const DiscoItem d = it->item();
	const Features &f = d.features();


	long id = 0;


	if (f.canCommand() ) {
		id = Features::FID_AHCommand;
	}
	if (!d.identities().isEmpty()) {

		DiscoItem::Identity ident = d.identities().first();
		bool searchFirst = ident.category == "service" && ident.type == "jud";

		if ( searchFirst && f.canSearch() ) {
			id = Features::FID_Search;
		}
		else if ( ident.category == "conference" &&  f.canGroupchat() ) {
			id = Features::FID_Groupchat;
		}
		else if ( f.canRegister() ) {
				id = Features::FID_Register;
		}
	}

	if ( id > 0 ) {
		if ( !it->isOpen() ) {
			if ( it->isExpandable() || it->childCount() )
				it->setOpen( true );
		}
		else {
			it->setOpen( false );
		}
		emit dlg->featureActivated( Features::feature(id), d.jid(), d.node() );
	}
}
