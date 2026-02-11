editViewPSW()
{
	bool newVal = ui.actionView_PSW->isChecked();
	Preferences::getInstance().setRegs(Preferences::ViewPsw, newVal);
	mPsw->setVisible(newVal, Preferences::getInstance().theme() == Preferences::Modern);
	if (Preferences::getInstance().pswMode() == Psw::Docked)
	{
		mPswDock->setVisible(newVal);
	}
 }
