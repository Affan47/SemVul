soundChanged(bool yes)
{
	KConfigGroup configGroup(KGlobal::config(), "Settings"); configGroup.writeEntry("sound", yes); configGroup.sync();
}
