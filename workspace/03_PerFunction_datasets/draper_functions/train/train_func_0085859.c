setupMenus()
{


    fileMenu = new QMenu(_q("File"), _window.get());
    fileMenu->addAction(propertiesAction);
    fileMenu->addAction(quitAction);


    editMenu = new QMenu(_q("Edit"), _window.get());
    editMenu->addAction(preferencesAction);


    movieControlMenu = new QMenu(_q("Movie Control"), _window.get());
    movieControlMenu->addAction(playAction);
    movieControlMenu->addAction(pauseAction);
    movieControlMenu->addAction(stopAction);
    movieControlMenu->addAction(restartAction);


    viewMenu = new QMenu(_q("View"), _window.get());
    viewMenu->addAction(refreshAction);
    viewMenu->addAction(fullscreenAction);
}
