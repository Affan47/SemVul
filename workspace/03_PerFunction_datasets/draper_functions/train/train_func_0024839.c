ODM_CmnInfoUpdate(struct odm_dm_struct *pDM_Odm, u32 CmnInfo, u64 Value)
{


	switch	(CmnInfo) {
	case	ODM_CMNINFO_ABILITY:
		pDM_Odm->SupportAbility = (u32)Value;
		break;
	case	ODM_CMNINFO_RF_TYPE:
		pDM_Odm->RFType = (u8)Value;
		break;
	case	ODM_CMNINFO_WIFI_DIRECT:
		pDM_Odm->bWIFI_Direct = (bool)Value;
		break;
	case	ODM_CMNINFO_WIFI_DISPLAY:
		pDM_Odm->bWIFI_Display = (bool)Value;
		break;
	case	ODM_CMNINFO_LINK:
		pDM_Odm->bLinked = (bool)Value;
		break;
	case	ODM_CMNINFO_RSSI_MIN:
		pDM_Odm->RSSI_Min = (u8)Value;
		break;
	case	ODM_CMNINFO_DBG_COMP:
		pDM_Odm->DebugComponents = Value;
		break;
	case	ODM_CMNINFO_DBG_LEVEL:
		pDM_Odm->DebugLevel = (u32)Value;
		break;
	case	ODM_CMNINFO_RA_THRESHOLD_HIGH:
		pDM_Odm->RateAdaptive.HighRSSIThresh = (u8)Value;
		break;
	case	ODM_CMNINFO_RA_THRESHOLD_LOW:
		pDM_Odm->RateAdaptive.LowRSSIThresh = (u8)Value;
		break;
	}
}
