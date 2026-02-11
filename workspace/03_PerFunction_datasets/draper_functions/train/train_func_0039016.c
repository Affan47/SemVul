sms_to_string (struct sms* self) {
	gchar* result = NULL;
	GSList* list = NULL;
	GSList* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
#line 482 "../src/lib/fsogsm3rdparty.vapi"
	g_return_val_if_fail (self != NULL, NULL);
#line 484 "../src/lib/fsogsm3rdparty.vapi"
	list = NULL;
#line 485 "../src/lib/fsogsm3rdparty.vapi"
	list = g_slist_append (list, self);
#line 486 "../src/lib/fsogsm3rdparty.vapi"
	_tmp0_ = list;
#line 486 "../src/lib/fsogsm3rdparty.vapi"
	_tmp1_ = sms_decode_text (_tmp0_);
#line 486 "../src/lib/fsogsm3rdparty.vapi"
	result = _tmp1_;
#line 486 "../src/lib/fsogsm3rdparty.vapi"
	_g_slist_free0 (list);
#line 486 "../src/lib/fsogsm3rdparty.vapi"
	return result;
#line 320 "testsms.c"
}
