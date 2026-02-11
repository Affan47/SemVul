statuscode2dpmstatus(int statuscode, int isfile)
{
	switch (statuscode) {
	case SRM_USCORESUCCESS:
		return (DPM_SUCCESS);
	case SRM_USCOREFILE_USCORELIFETIME_USCOREEXPIRED:
		return (DPM_EXPIRED);
	case SRM_USCOREREQUEST_USCOREQUEUED:
		return (DPM_QUEUED);
	case SRM_USCOREREQUEST_USCOREINPROGRESS:
		return (DPM_ACTIVE);
	case SRM_USCOREABORTED:
		return (DPM_ABORTED);
	case SRM_USCORERELEASED:
		return (DPM_RELEASED);
	case SRM_USCOREFILE_USCOREPINNED:
		return (DPM_READY);
	case SRM_USCOREFILE_USCOREIN_USCORECACHE:
		return (DPM_SUCCESS);
	case SRM_USCORESPACE_USCOREAVAILABLE:
		return (DPM_READY);
	case SRM_USCOREPARTIAL_USCORESUCCESS:
		return (DPM_DONE);
	default:
		if (isfile)
			return (DPM_FAILED | statuscode2serrno (statuscode));
		serrno = statuscode2serrno (statuscode);
		return (-1);
	}
}
