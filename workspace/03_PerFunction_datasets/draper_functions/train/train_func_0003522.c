getAvatar(const Jid& _jid)
{


	Jid jid = _jid;


	Avatar* av = retrieveAvatar(jid);


	if (av != active_avatars_[jid.full()]) {
		active_avatars_[jid.full()] = av;
		active_avatars_[jid.bare()] = av;
		emit avatarChanged(jid);
	}

	QPixmap pm = (av ? av->getPixmap() : QPixmap());
	pm = ensureSquareAvatar(pm);


	PsiIcon icon;
	icon.setImpix(pm);
	iconset_.setIcon(QString("avatars/%1").arg(jid.bare()),icon);

	return pm;
}
