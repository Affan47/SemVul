CreatePrefDialog()
{
    mPrefDialog = new PrefDialog(this);
    mPrefDialog->setModal(true);
    mPrefDialog->InitSettings();
    connect(mPrefDialog, SIGNAL(accepted()), this, SLOT(ApplyPreferencesSlot()));
    connect(mPrefDialog, SIGNAL(accepted()), mGameTablesDialog, SLOT(SetSettingsSlot()));
    connect(mPrefDialog, SIGNAL(ResetColorOrderSignal()), mPegFactory, SLOT(ResetColorsOrderSlot()));
}
