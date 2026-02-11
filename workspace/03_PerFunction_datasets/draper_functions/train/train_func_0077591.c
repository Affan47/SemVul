test_fso_sms_storage_add_single (void) {
	FsoGsmISmsStorage* storage = NULL;
	FsoGsmISmsStorage* _tmp0_ = NULL;
	struct sms* sms = NULL;
	struct sms* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
#line 32 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_tmp0_ = fso_gsm_sms_storage_factory_create ("default", IMSI);
#line 32 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	storage = _tmp0_;
#line 33 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	fso_gsm_isms_storage_clean (storage);
#line 35 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_tmp1_ = sms_newFromHexPdu (pdu3, pdulength3);
#line 35 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	sms = _tmp1_;
#line 36 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_vala_assert (sms != NULL, "sms != null");
#line 39 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_tmp2_ = fso_gsm_isms_storage_addSms (storage, sms);
#line 39 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_vala_assert (_tmp2_ == FSO_GSM_SMS_STORAGE_SMS_SINGLE_COMPLETE, "storage.addSms( sms ) == SmsStorage.SMS_SINGLE_COMPLETE");
#line 42 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_tmp3_ = fso_gsm_isms_storage_addSms (storage, sms);
#line 42 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_vala_assert (_tmp3_ == FSO_GSM_SMS_STORAGE_SMS_ALREADY_SEEN, "storage.addSms( sms ) == SmsStorage.SMS_ALREADY_SEEN");
#line 30 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_sms_free0 (sms);
#line 30 "/tmp/buildd/fso-gsmd-0.12.0/tests/testsmsstorage.vala"
	_g_object_unref0 (storage);
#line 241 "testsmsstorage.c"
}
