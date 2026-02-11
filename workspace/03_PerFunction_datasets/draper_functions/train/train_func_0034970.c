registerCaps(const CapsSpec& spec,const XMPP::DiscoItem::Identities& identities,const XMPP::Features& features)
{
	if (!isRegistered(spec)) {
		CapsInfo info;
		info.setIdentities(identities);
		info.setFeatures(features);
		capsInfo_[spec] = info;
		emit registered(spec);
	}
}
