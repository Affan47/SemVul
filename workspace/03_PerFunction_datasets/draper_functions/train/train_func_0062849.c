save_breusch_pagan_result (panelmod_t *pan)
{
    ModelTest *test;

    if (pan->realmod == NULL || na(pan->BP)) {
	return;
    }

    test = model_test_new(GRETL_TEST_PANEL_BP);

    if (test != NULL) {
	model_test_set_teststat(test, GRETL_STAT_WALD_CHISQ);
	model_test_set_dfn(test, 1);
	model_test_set_value(test, pan->BP);
	model_test_set_pvalue(test, chisq_cdf_comp(1, pan->BP));
	maybe_add_test_to_model(pan->realmod, test);
    }
}
