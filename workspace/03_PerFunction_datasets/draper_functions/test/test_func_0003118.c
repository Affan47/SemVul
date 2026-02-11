updateCaps(const Jid& jid, const QString& node, const QString& ver, const QString& ext)
{
	if (jid.compare(jid_,false))
		return;

	CapsSpec c(node,ver,ext);
	CapsSpecs caps = c.flatten();
	if (capsSpecs_[jid.full()] != c) {


		CapsSpecs old_caps = capsSpecs_[jid.full()].flatten();
		foreach(CapsSpec s, old_caps) {
			if (s != CapsSpec()) {
				capsJids_[s].removeAll(jid.full());
			}
		}

		if (!node.isEmpty() && !ver.isEmpty()) {

			capsSpecs_[jid.full()] = c;
			foreach(CapsSpec s, caps) {
				if (!capsJids_[s].contains(jid.full())) {
					capsJids_[s].push_back(jid.full());
				}
			}

			emit capsChanged(jid);


			if (isEnabled()) {
				foreach(CapsSpec s, caps) {
					if (!registry_->isRegistered(s) && capsJids_[s].count() == 1) {

						discoInfoQuerier_->getDiscoInfo(jid,node + "#" + s.extensions());
					}
				}
			}
		}
		else {

			qWarning(QString("caps.cpp: Illegal caps info from %1: node=%2, ver=%3").arg(QString(jid.full()).replace('%',"%%")).arg(node).arg(ver).toAscii());
			capsSpecs_.remove(jid.full());
		}
	}
	else {

		foreach(CapsSpec s, caps) {
			capsJids_[s].push_back(jid.full());
		}
	}
}
