MR_GetSpanBlock(u32 ld, u64 row, u64 *span_blk,
		    struct MR_DRV_RAID_MAP_ALL *map)
{
	struct MR_SPAN_BLOCK_INFO *pSpanBlock = MR_LdSpanInfoGet(ld, map);
	struct MR_QUAD_ELEMENT    *quad;
	struct MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	u32                span, j;

	for (span = 0; span < raid->spanDepth; span++, pSpanBlock++) {

		for (j = 0; j < le32_to_cpu(pSpanBlock->block_span_info.noElements); j++) {
			quad = &pSpanBlock->block_span_info.quad[j];

			if (le32_to_cpu(quad->diff) == 0)
				return SPAN_INVALID;
			if (le64_to_cpu(quad->logStart) <= row && row <=
				le64_to_cpu(quad->logEnd) && (mega_mod64(row - le64_to_cpu(quad->logStart),
				le32_to_cpu(quad->diff))) == 0) {
				if (span_blk != NULL) {
					u64  blk, debugBlk;
					blk =  mega_div64_32((row-le64_to_cpu(quad->logStart)), le32_to_cpu(quad->diff));
					debugBlk = blk;

					blk = (blk + le64_to_cpu(quad->offsetInSpan)) << raid->stripeShift;
					*span_blk = blk;
				}
				return span;
			}
		}
	}
	return SPAN_INVALID;
}
