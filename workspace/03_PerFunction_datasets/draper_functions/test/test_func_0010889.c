setItem(CanvasItem *item)
{
	delete config;
	config = item->config(this);
	if (!config)
		return;
	config->ctorDone();
	hlayout->addWidget(config);
	hlayout->setStretchFactor(config, 2);
	config->setFrameStyle(QFrame::Box | QFrame::Raised);
	config->setLineWidth(1);
	config->show();
	connect(config, SIGNAL(modified()), this, SIGNAL(changed()));
}
