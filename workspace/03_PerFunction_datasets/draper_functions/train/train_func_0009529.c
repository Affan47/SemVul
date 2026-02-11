rndis_error_status(__le32 rndis_status)
{
	int ret = -EINVAL;
	switch (le32_to_cpu(rndis_status)) {
	case RNDIS_STATUS_SUCCESS:
		ret = 0;
		break;
	case RNDIS_STATUS_FAILURE:
	case RNDIS_STATUS_INVALID_DATA:
		ret = -EINVAL;
		break;
	case RNDIS_STATUS_NOT_SUPPORTED:
		ret = -EOPNOTSUPP;
		break;
	case RNDIS_STATUS_ADAPTER_NOT_READY:
	case RNDIS_STATUS_ADAPTER_NOT_OPEN:
		ret = -EBUSY;
		break;
	}
	return ret;
}
