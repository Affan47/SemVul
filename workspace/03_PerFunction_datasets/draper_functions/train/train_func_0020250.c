hal_EfusePgPacketWriteHeader(
				struct adapter *pAdapter,
				u8 efuseType,
				u16				*pAddr,
				struct pgpkt *pTargetPkt)
{
	bool bRet = false;

	if (pTargetPkt->offset >= EFUSE_MAX_SECTION_BASE)
		bRet = hal_EfusePgPacketWrite2ByteHeader(pAdapter, efuseType, pAddr, pTargetPkt);
	else
		bRet = hal_EfusePgPacketWrite1ByteHeader(pAdapter, efuseType, pAddr, pTargetPkt);

	return bRet;
}
