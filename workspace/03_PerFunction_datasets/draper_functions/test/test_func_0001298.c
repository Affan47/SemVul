widget()
{
	if ( w )
		return 0;

	w = new OptStatusUI();
	OptStatusUI *d = (OptStatusUI *)w;

	QString s = tr("Makes Psi automatically set your status to \"away\" if your"
		" computer is idle for the specified amount of time.");
	QWhatsThis::add(d->ck_asAway, s);
	QWhatsThis::add(d->sb_asAway, s);
	s = tr("Makes Psi automatically set your status to \"extended away\" if your"
		" computer is idle for the specified amount of time.");
	QWhatsThis::add(d->ck_asXa, s);
	QWhatsThis::add(d->sb_asXa, s);
	s = tr("Makes Psi automatically set your status to \"offline\" if your"
		" computer is idle for the specified amount of time."
		"  This will disconnect you from the Jabber server.");
	if (!PsiOptions::instance()->getOption("options.ui.menu.status.xa").toBool()) {
		d->ck_asXa->hide();
		d->sb_asXa->hide();
		d->lb_asXa->hide();
	}
	QWhatsThis::add(d->ck_asOffline, s);
	QWhatsThis::add(d->sb_asOffline, s);

	QWhatsThis::add(d->te_asMessage,
		tr("Specifies an extended message to use if you allow Psi"
		" to set your status automatically.  See options above."));

	setStatusPresetWidgetsEnabled(false);
	connect(d->pb_spNew, SIGNAL(clicked()), SLOT(newStatusPreset()));
	connect(d->pb_spDelete, SIGNAL(clicked()), SLOT(removeStatusPreset()));
	connect(d->cb_preset, SIGNAL(currentIndexChanged(int)), SLOT(selectStatusPreset(int)));
	connect(d->te_sp, SIGNAL(textChanged()), SLOT(changeStatusPreset()));
	connect(d->le_sp_priority, SIGNAL(textChanged(const QString&)), SLOT(changeStatusPreset()));
	connect(d->cb_sp_status, SIGNAL(activated(int)), SLOT(changeStatusPreset()));

	QWhatsThis::add(d->pb_spNew,
		tr("Press this button to create a new status message preset."));
	QWhatsThis::add(d->pb_spDelete,
		tr("Press this button to delete a status message preset."));
	QWhatsThis::add(d->cb_preset,
		tr("Use this list to select a status message preset"
		" to view or edit in the box to the bottom."));
	QWhatsThis::add(d->te_sp,
		tr("You may edit the message here for the currently selected"
		" status message preset in the list to the above."));
	QWhatsThis::add(d->cb_sp_status,
		tr("Use this to choose the status that will be assigned to this preset"));
	QWhatsThis::add(d->le_sp_priority,
		tr("Fill in the priority that will be assigned to this preset."
		   " If no priority is given, the default account priority will be used."));

	QWhatsThis::add(d->ck_askOnline,
		tr("Jabber allows you to put extended status messages on"
		" all status types.  Normally, Psi does not prompt you for"
		" an extended message when you set your status to \"online\"."
		"  Check this option if you want to have this prompt."));

	return w;
}
