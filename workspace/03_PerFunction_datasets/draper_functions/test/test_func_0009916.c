qt_connectToServer()
{
	if (!qt_initialized)
		return;


	bool connectToWidget = !qt_optionWidget.isEmpty();
	QString server = connectToWidget ? qt_optionWidget : qt_localServerName;

	if (qt_socket.state() == QLocalSocket::ConnectedState)
	{

		if (qt_socket.serverName() == server)
			return;


		qt_socket.disconnectFromServer();
		while (qt_socket.state() == QLocalSocket::ConnectedState)
			qt_socket.waitForDisconnected(1000);
	}


	if (!connectToWidget && !qt_gnuplot_qtStarted)
		execGnuplotQt();


	qt_connectToServer(server);
}
