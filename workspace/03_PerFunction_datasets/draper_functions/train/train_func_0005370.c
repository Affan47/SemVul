cleanup()
{
    if (app->servicePid > 0) {
        mprLog(1, "%s: Killing %s at pid %d with signal %d", app->appName, app->serviceProgram,
            app->servicePid, app->signal);
        kill(app->servicePid, app->signal);
        app->servicePid = 0;
    }
}
