wispr_portal_error(struct connman_wispr_portal_context *wp_context)
{
	DBG("Failed to proceed wispr/portal web request");

	wp_context->wispr_result = CONNMAN_WISPR_RESULT_FAILED;
}
