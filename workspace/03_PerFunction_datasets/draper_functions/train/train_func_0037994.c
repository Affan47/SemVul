ODM_CmnInfoInit23a(struct dm_odm_t *pDM_Odm,
		enum odm_cmninfo CmnInfo,
		u32 Value
	)
{


	switch	(CmnInfo) {

	case	ODM_CMNINFO_MP_TEST_CHIP:
		pDM_Odm->bIsMPChip = (u8)Value;
		break;
	case	ODM_CMNINFO_IC_TYPE:
		pDM_Odm->SupportICType = Value;
		break;
	case	ODM_CMNINFO_CUT_VER:
		pDM_Odm->CutVersion = (u8)Value;
		break;
	case	ODM_CMNINFO_FAB_VER:
		pDM_Odm->FabVersion = (u8)Value;
		break;
	case	ODM_CMNINFO_BOARD_TYPE:
		pDM_Odm->BoardType = (u8)Value;
		break;
	case	ODM_CMNINFO_EXT_LNA:
		pDM_Odm->ExtLNA = (u8)Value;
		break;
	case	ODM_CMNINFO_EXT_PA:
		pDM_Odm->ExtPA = (u8)Value;
		break;
	case	ODM_CMNINFO_EXT_TRSW:
		pDM_Odm->ExtTRSW = (u8)Value;
		break;
	case	ODM_CMNINFO_BINHCT_TEST:
		pDM_Odm->bInHctTest = (bool)Value;
		break;
	case	ODM_CMNINFO_BWIFI_TEST:
		pDM_Odm->bWIFITest = (bool)Value;
		break;
	case	ODM_CMNINFO_SMART_CONCURRENT:
		pDM_Odm->bDualMacSmartConcurrent = (bool)Value;
		break;

	default:

		break;
	}
}
