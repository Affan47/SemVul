applyView()
{
	if (vphantomRB->isChecked())
		params_.type = InsetPhantomParams::VPhantom;
	else if (hphantomRB->isChecked())
		params_.type = InsetPhantomParams::HPhantom;
	else
		params_.type = InsetPhantomParams::Phantom;
}
