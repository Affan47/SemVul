AddECValues(CECTag* tag) const
{
	tag->AddTag(CECTag(EC_TAG_STAT_NODE_VALUE, (uint64)theStats::GetPeakConnections()));
}
