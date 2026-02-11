LoadOldAdunanzAStatistics_single(wxConfigBase* cfg, const wxString& entryName, uint64_t& gotValue, bool& cfgChanged)
{
	if (!cfg) return;
	if (entryName.IsEmpty()) return;

	if (cfg->HasEntry(entryName)) {
		gotValue += ReadUInt64FromCfg(cfg, entryName);
		cfg->DeleteEntry(entryName);
		cfgChanged = true;
	}

}
