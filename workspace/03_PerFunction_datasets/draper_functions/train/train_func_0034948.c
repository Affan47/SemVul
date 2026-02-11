setOwner(KPlayer* owner)
{

 d->mOwner = owner;
 for (int i = 0; i < d->mConfigWidgets.count(); i++) {
	if (d->mConfigWidgets.at(i)) {
		d->mConfigWidgets.at(i)->setOwner(d->mOwner);
	} else {
		kError(11001) << "NULL widget??";
	}
 }
}
