do_deinit (app_t app)
{
  if (app && app->app_local)
    {
      xfree (app->app_local->cardno);
      xfree (app->app_local->country);
      xfree (app->app_local);
      app->app_local = NULL;
    }
}
