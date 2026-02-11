AddECValues(CECTag *tag) const
{
	CECTag value(EC_TAG_STAT_NODE_VALUE, m_bytes);
	value.AddTag(CECTag(EC_TAG_STAT_VALUE_TYPE, (uint8)EC_VALUE_BYTES));
	CECTag tmp(EC_TAG_STAT_NODE_VALUE, (uint64)m_packets);
	tmp.AddTag(CECTag(EC_TAG_STAT_VALUE_TYPE, (uint8)EC_VALUE_ISHORT));
	value.AddTag(tmp);
	tag->AddTag(value);
}
