pdfapp_postblit(pdfapp_t *app)
{
	clock_t time;
	float seconds;
	int llama;

	app->transitions_enabled = 1;
	if (!app->in_transit)
		return;
	time = clock();
	seconds = (float)(time - app->start_time) / CLOCKS_PER_SEC;
	llama = seconds * 256 / app->transition.duration;
	if (llama >= 256)
	{

		app->in_transit = 0;
		fz_drop_pixmap(app->ctx, app->image);
		app->image = app->new_image;
		app->new_image = NULL;
		fz_drop_pixmap(app->ctx, app->old_image);
		app->old_image = NULL;
		if (app->duration != 0)
			winadvancetimer(app, app->duration);
	}
	else
		fz_generate_transition(app->image, app->old_image, app->new_image, llama, &app->transition);
	winrepaint(app);
}
