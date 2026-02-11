askSave(bool noMoreChances)
{
	if (!modified)

		return false;

	int result = KMessageBox::warningYesNoCancel(this, i18n("There are unsaved changes to current hole. Save them?"), i18n("Unsaved Changes"), KStandardGuiItem::save(), noMoreChances? KStandardGuiItem::discard() : KGuiItem(i18n("Save &Later")), KStandardGuiItem::cancel(), noMoreChances? "DiscardAsk" : "SaveAsk");
	switch (result)
	{
		case KMessageBox::Yes:
			save();


		case KMessageBox::No:
			return false;
			break;

		case KMessageBox::Cancel:
			return true;
			break;

		default:
			break;
	}

	return false;
}
