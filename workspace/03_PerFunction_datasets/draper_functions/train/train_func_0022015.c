hdp_application_unref(struct hdp_application *app)
{
	if (app == NULL)
		return;

	app->ref--;

	DBG("health_application_unref(%p): ref=%d", app, app->ref);
	if (app->ref > 0)
		return;

	hdp_free_application(app);
}
