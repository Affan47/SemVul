link_timer_hdl(unsigned long data)
{
	struct rtw_adapter *padapter = (struct rtw_adapter *)data;


	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;


	if (pmlmeinfo->state & WIFI_FW_AUTH_NULL) {
		DBG_8723A("link_timer_hdl:no beacon while connecting\n");
		pmlmeinfo->state = MSR_NOLINK;
		report_join_res23a(padapter, -3);
	} else if (pmlmeinfo->state & WIFI_FW_AUTH_STATE) {

		if (++pmlmeinfo->reauth_count > REAUTH_LIMIT) {


				pmlmeinfo->state = 0;
				report_join_res23a(padapter, -1);
				return;


		}

		DBG_8723A("link_timer_hdl: auth timeout and try again\n");
		pmlmeinfo->auth_seq = 1;
		issue_auth(padapter, NULL, 0);
		set_link_timer(pmlmeext, REAUTH_TO);
	} else if (pmlmeinfo->state & WIFI_FW_ASSOC_STATE) {

		if (++pmlmeinfo->reassoc_count > REASSOC_LIMIT) {
			pmlmeinfo->state = MSR_NOLINK;
			report_join_res23a(padapter, -2);
			return;
		}

		DBG_8723A("link_timer_hdl: assoc timeout and try again\n");
		issue_assocreq(padapter);
		set_link_timer(pmlmeext, REASSOC_TO);
	}

	return;
}
