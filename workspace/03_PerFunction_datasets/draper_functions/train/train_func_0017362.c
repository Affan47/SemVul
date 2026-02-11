showStatus(const QString& msg, int progress)
{
	static bool msgUpdateNeeded = true;

	if (!_statusbar) return;

	if (msg.isEmpty()) {

		if (_progressBar) {
		    _statusbar->removeWidget(_progressBar);
		    delete _progressBar;
		    _progressBar = 0;
		}
		_statusbar->clearMessage();
		_progressMsg = msg;
		return;
	}

	if (_progressMsg.isEmpty())
		_progressStart.start();

	if (msg != _progressMsg) {
		_progressMsg = msg;
		msgUpdateNeeded = true;
	}


	if (_progressStart.elapsed() < 500)
		return;

	if (!_progressBar) {
		_progressBar = new QProgressBar(_statusbar);
		_progressBar->setMaximumSize(200, _statusbar->height()-4);
		_statusbar->addPermanentWidget(_progressBar, 1);
		_progressBar->show();
		msgUpdateNeeded = true;
	}

	_progressStart.restart();

	if (msgUpdateNeeded) {
		_statusbar->showMessage(msg);
		msgUpdateNeeded = false;
	}
	_progressBar->setValue(progress);


	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}
