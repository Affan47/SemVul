ODM_CmnInfoInit(struct odm_dm_struct *pDM_Odm, enum odm_common_info_def CmnInfo, u32 Value)
{

	switch	(CmnInfo) {

	case	ODM_CMNINFO_ABILITY:
		pDM_Odm->SupportAbility = (u32)Value;
		break;
	case	ODM_CMNINFO_PLATFORM:
		pDM_Odm->SupportPlatform = (u8)Value;
		break;
	case	ODM_CMNINFO_INTERFACE:
		pDM_Odm->SupportInterface = (u8)Value;
		break;
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
	case	ODM_CMNINFO_RF_TYPE:
		pDM_Odm->RFType = (u8)Value;
		break;
	case    ODM_CMNINFO_RF_ANTENNA_TYPE:
		pDM_Odm->AntDivType = (u8)Value;
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
	case	ODM_CMNINFO_PATCH_ID:
		pDM_Odm->PatchID = (u8)Value;
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


	pDM_Odm->BbSwingIdxOfdm			= 12;
	pDM_Odm->BbSwingIdxOfdmCurrent	= 12;
	pDM_Odm->BbSwingFlagOfdm		= false;
}
