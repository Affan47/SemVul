createCentralWidget()
{
    stackedWidget = new QStackedWidget(this);
    startWidget = new StartWidget(this);
    fileWidget = new FileWidget(this);
    eventsWidget = new EventsWidget(this);
    eventsWidget->mainWindow = this;

    stackedWidget->addWidget(startWidget);
    stackedWidget->addWidget(fileWidget);
    stackedWidget->addWidget(eventsWidget);

    setCentralWidget(stackedWidget);
}
