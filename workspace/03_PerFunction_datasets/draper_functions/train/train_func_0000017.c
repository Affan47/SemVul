test_ctzv_to_timezone (void) {
	gint tz1 = 0;
	gint _tmp0_ = 0;
	gint tz2 = 0;
	gint _tmp1_ = 0;
	gint tz3 = 0;
	gint _tmp2_ = 0;
#line 26 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	_tmp0_ = fso_gsm_constants_ctzvToTimeZone (0x19);
#line 26 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	tz1 = _tmp0_;
#line 27 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	_vala_assert (tz1 == (-165), "tz1 == -165");
#line 29 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	_tmp1_ = fso_gsm_constants_ctzvToTimeZone (35);
#line 29 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	tz2 = _tmp1_;
#line 30 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	_vala_assert (tz2 == (8 * 60), "tz2 == 8*60");
#line 32 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	_tmp2_ = fso_gsm_constants_ctzvToTimeZone (105);
#line 32 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	tz3 = _tmp2_;
#line 33 "/tmp/buildd/fso-gsmd-0.12.0/tests/testconst.vala"
	_vala_assert (tz3 == ((-4) * 60), "tz3 == -4*60");
#line 69 "testconst.c"
}
