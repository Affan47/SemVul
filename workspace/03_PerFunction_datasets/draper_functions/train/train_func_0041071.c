clientVersion(const Jid& jid) const
{
	return (capsEnabled(jid) ? capsSpecs_[jid.full()].version() : QString());
}
