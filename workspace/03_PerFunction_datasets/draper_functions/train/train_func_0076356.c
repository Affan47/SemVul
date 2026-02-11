startOutput(void)
{
	open();
	notifier=new QSocketNotifier(device,QSocketNotifier::Write);
	connect(notifier,SIGNAL(activated(int)),this,SLOT(checkSpace(int)));
	return speed/20;
}
