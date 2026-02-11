cleanupPage()
{
    updateValues.stop();
    if (wizard->controller) {
        wizard->controller->stop();
#ifdef WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
        delete wizard->controller;
        wizard->controller = NULL;
    }
}
