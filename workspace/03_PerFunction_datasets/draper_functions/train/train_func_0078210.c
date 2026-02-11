restoreOptions()
{
	if ( !w )
		return;

	GeneralGroupchatUI *d = (GeneralGroupchatUI *)w;


	disconnect(d->le_newNickColor,     SIGNAL(textChanged(const QString &)), 0, 0);
	disconnect(d->le_newHighlightWord, SIGNAL(textChanged(const QString &)), 0, 0);
	connect(d->le_newNickColor,	   SIGNAL(textChanged(const QString &)), SLOT(displayGCNickColor()));

	d->ck_gcHighlights->setChecked( true );
	d->ck_gcHighlights->setChecked( PsiOptions::instance()->getOption("options.ui.muc.use-highlighting").toBool() );
	d->ck_gcNickColoring->setChecked( true );
	d->ck_gcNickColoring->setChecked( PsiOptions::instance()->getOption("options.ui.muc.use-nick-coloring").toBool() );
	d->lw_highlightWords->clear();
	d->lw_highlightWords->addItems( PsiOptions::instance()->getOption("options.ui.muc.highlight-words").toStringList() );
	d->lw_nickColors->clear();


	foreach(QString col, PsiOptions::instance()->getOption("options.ui.look.colors.muc.nick-colors").toStringList()) {
		addNickColor(col);
	}

	d->le_newHighlightWord->setText("");
	d->le_newNickColor->setText("#FFFFFF");
}
