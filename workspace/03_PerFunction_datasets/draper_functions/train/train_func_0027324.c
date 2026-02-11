displayGCNickColor()
{
	GeneralGroupchatUI *d = (GeneralGroupchatUI *)w;
	d->pb_nickColor->setPixmap( name2color(d->le_newNickColor->text()) );
}
