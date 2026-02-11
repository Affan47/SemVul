EFUSE_GetEfuseDefinition(struct adapter *pAdapter, u8 efuseType, u8 type, void *pOut)
{
	switch (type) {
	case TYPE_EFUSE_MAX_SECTION:
		{
			u8 *pMax_section;
			pMax_section = pOut;
			*pMax_section = EFUSE_MAX_SECTION_88E;
		}
		break;
	case TYPE_EFUSE_REAL_CONTENT_LEN:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;
			*pu2Tmp = EFUSE_REAL_CONTENT_LEN_88E;
		}
		break;
	case TYPE_EFUSE_CONTENT_LEN_BANK:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;
			*pu2Tmp = EFUSE_REAL_CONTENT_LEN_88E;
		}
		break;
	case TYPE_AVAILABLE_EFUSE_BYTES_BANK:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;
			*pu2Tmp = (u16)(EFUSE_REAL_CONTENT_LEN_88E-EFUSE_OOB_PROTECT_BYTES_88E);
		}
		break;
	case TYPE_AVAILABLE_EFUSE_BYTES_TOTAL:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;
			*pu2Tmp = (u16)(EFUSE_REAL_CONTENT_LEN_88E-EFUSE_OOB_PROTECT_BYTES_88E);
		}
		break;
	case TYPE_EFUSE_MAP_LEN:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;
			*pu2Tmp = (u16)EFUSE_MAP_LEN_88E;
		}
		break;
	case TYPE_EFUSE_PROTECT_BYTES_BANK:
		{
			u8 *pu1Tmp;
			pu1Tmp = pOut;
			*pu1Tmp = (u8)(EFUSE_OOB_PROTECT_BYTES_88E);
		}
		break;
	default:
		{
			u8 *pu1Tmp;
			pu1Tmp = pOut;
			*pu1Tmp = 0;
		}
		break;
	}
}
