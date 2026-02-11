capi20_get_manufacturer(u32 contr, u8 *buf)
{
	struct capi_ctr *ctr;
	u16 ret;

	if (contr == 0) {
		strlcpy(buf, capi_manufakturer, CAPI_MANUFACTURER_LEN);
		return CAPI_NOERROR;
	}

	mutex_lock(&capi_controller_lock);

	ctr = get_capi_ctr_by_nr(contr);
	if (ctr && ctr->state == CAPI_CTR_RUNNING) {
		strlcpy(buf, ctr->manu, CAPI_MANUFACTURER_LEN);
		ret = CAPI_NOERROR;
	} else
		ret = CAPI_REGNOTINSTALLED;

	mutex_unlock(&capi_controller_lock);
	return ret;
}
