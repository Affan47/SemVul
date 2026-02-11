GetGapSize(uint16 part) const
{
	uint64 uRangeStart = part * PARTSIZE;
	uint64 uRangeEnd = uRangeStart + GetPartSize(part) - 1;
	uint64 uTotalGapSize = 0;


	ListType::const_iterator it = m_gaplist.lower_bound(uRangeStart);
	for (; it != m_gaplist.end(); ++it) {
		uint64 curGapStart = it->second;
		uint64 curGapEnd   = it->first;

		if (curGapStart <= uRangeStart && curGapEnd >= uRangeEnd) {

			uTotalGapSize += uRangeEnd - uRangeStart + 1;
			break;
		} else if (curGapStart >= uRangeStart) {
			if (curGapStart <= uRangeEnd) {

				uTotalGapSize += std::min(curGapEnd, uRangeEnd) - curGapStart + 1;
			} else {

				break;
			}
		} else if (curGapEnd >= uRangeStart && curGapEnd <= uRangeEnd) {

			uTotalGapSize += curGapEnd - uRangeStart + 1;
		}
	}

	wxASSERT( uTotalGapSize <= uRangeEnd - uRangeStart + 1 );
	return uTotalGapSize;
}
