Tspi_TPM_GetStatus(TSS_HTPM hTPM,
		   TSS_FLAG statusFlag,
		   TSS_BOOL * pfTpmState)
{
	TSS_HCONTEXT tspContext;
	TSS_RESULT result;
	UINT32 nonVolFlags;
	UINT32 volFlags;

	if (pfTpmState == NULL)
		return TSPERR(TSS_E_BAD_PARAMETER);

	if ((result = obj_tpm_get_tsp_context(hTPM, &tspContext)))
		return result;

	if ((result = get_tpm_flags(tspContext, hTPM, &volFlags, &nonVolFlags)))
		return result;

	switch (statusFlag) {
	case TSS_TPMSTATUS_DISABLEOWNERCLEAR:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_DISABLEOWNERCLEAR_BIT);
		break;
	case TSS_TPMSTATUS_DISABLEFORCECLEAR:
		*pfTpmState = BOOL(volFlags & TSS_TPM_SF_DISABLEFORCECLEAR_BIT);
		break;
	case TSS_TPMSTATUS_DISABLED:
	case TSS_TPMSTATUS_OWNERSETDISABLE:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_DISABLE_BIT);
		break;
	case TSS_TPMSTATUS_DEACTIVATED:
	case TSS_TPMSTATUS_PHYSICALSETDEACTIVATED:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_DEACTIVATED_BIT);
		break;
	case TSS_TPMSTATUS_SETTEMPDEACTIVATED:
		*pfTpmState = BOOL(volFlags & TSS_TPM_SF_DEACTIVATED_BIT);
		break;
	case TSS_TPMSTATUS_SETOWNERINSTALL:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_OWNERSHIP_BIT);
		break;
	case TSS_TPMSTATUS_DISABLEPUBEKREAD:
		*pfTpmState = INVBOOL(nonVolFlags & TSS_TPM_PF_READPUBEK_BIT);
		break;
	case TSS_TPMSTATUS_ALLOWMAINTENANCE:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_ALLOWMAINTENANCE_BIT);
		break;
	case TSS_TPMSTATUS_MAINTENANCEUSED:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_MAINTENANCEDONE_BIT);
		break;
	case TSS_TPMSTATUS_PHYSPRES_LIFETIMELOCK:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_PHYSICALPRESENCELIFETIMELOCK_BIT);
		break;
	case TSS_TPMSTATUS_PHYSPRES_HWENABLE:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_PHYSICALPRESENCEHWENABLE_BIT);
		break;
	case TSS_TPMSTATUS_PHYSPRES_CMDENABLE:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_PHYSICALPRESENCECMDENABLE_BIT);
		break;
	case TSS_TPMSTATUS_CEKP_USED:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_CEKPUSED_BIT);
		break;
	case TSS_TPMSTATUS_PHYSPRESENCE:
		*pfTpmState = BOOL(volFlags & TSS_TPM_SF_PHYSICALPRESENCE_BIT);
		break;
	case TSS_TPMSTATUS_PHYSPRES_LOCK:
		*pfTpmState = BOOL(volFlags & TSS_TPM_SF_PHYSICALPRESENCELOCK_BIT);
		break;
	case TSS_TPMSTATUS_TPMPOST:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_TPMPOST_BIT);
		break;
	case TSS_TPMSTATUS_TPMPOSTLOCK:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_TPMPOSTLOCK_BIT);
		break;
	case TSS_TPMSTATUS_FIPS:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_FIPS_BIT);
		break;
	case TSS_TPMSTATUS_ENABLE_REVOKEEK:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_ENABLEREVOKEEK_BIT);
		break;
	case TSS_TPMSTATUS_TPM_ESTABLISHED:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_RESETESTABLISHMENTBIT_BIT);
		break;
	case TSS_TPMSTATUS_NV_LOCK:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_NV_LOCKED_BIT);
		break;
	case TSS_TPMSTATUS_POSTINITIALISE:

		result = TSPERR(TSS_E_NOTIMPL);
		break;
#ifdef TSS_BUILD_TSS12
	case TSS_TPMSTATUS_DISABLEPUBSRKREAD:
		*pfTpmState = INVBOOL(nonVolFlags & TSS_TPM_PF_READSRKPUB_BIT);
		break;
	case TSS_TPMSTATUS_OPERATORINSTALLED:
		*pfTpmState = BOOL(nonVolFlags & TSS_TPM_PF_OPERATOR_BIT);
		break;
#endif
	default:
		return TSPERR(TSS_E_BAD_PARAMETER);
		break;
	}

	return TSS_SUCCESS;
}
