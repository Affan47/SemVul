GNUNET_ARM_start_service (struct GNUNET_ARM_Handle *h,
			  const char *service_name,
			  struct GNUNET_TIME_Relative timeout,
			  GNUNET_ARM_Callback cb, void *cb_cls)
{
  struct RequestContext *sctx;
  struct GNUNET_CLIENT_Connection *client;
  size_t slen;

  LOG (GNUNET_ERROR_TYPE_DEBUG,
       _("Asked to start service `%s' within %llu ms\n"), service_name,
       (unsigned long long) timeout.rel_value);
  if (0 == strcasecmp ("arm", service_name))
  {
    slen = strlen ("arm") + 1;
    sctx = GNUNET_malloc (sizeof (struct RequestContext) + slen);
    sctx->h = h;
    sctx->callback = cb;
    sctx->cls = cb_cls;
    sctx->timeout = GNUNET_TIME_relative_to_absolute (timeout);
    memcpy (&sctx[1], service_name, slen);
    GNUNET_CLIENT_service_test ("arm", h->cfg, timeout, &arm_service_report,
				sctx);
    return;
  }
  if (h->client == NULL)
  {
    client = GNUNET_CLIENT_connect ("arm", h->cfg);
    if (client == NULL)
    {
      LOG (GNUNET_ERROR_TYPE_DEBUG,
	   "arm_api, GNUNET_CLIENT_connect returned NULL\n");
      cb (cb_cls, GNUNET_ARM_PROCESS_COMMUNICATION_ERROR);
      return;
    }
    LOG (GNUNET_ERROR_TYPE_DEBUG,
	 "arm_api, GNUNET_CLIENT_connect returned non-NULL\n");
    h->client = client;
  }
  LOG (GNUNET_ERROR_TYPE_DEBUG, "arm_api, h->client non-NULL\n");
  change_service (h, service_name, timeout, cb, cb_cls,
		  GNUNET_MESSAGE_TYPE_ARM_START);
}
