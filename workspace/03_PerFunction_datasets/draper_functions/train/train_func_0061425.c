error(QAbstractSocket::SocketError socketError)
	{
		Q_UNUSED(socketError)

		if(mOnError.isValid())
			mOnError.call(thisObject(), QScriptValueList() << mUdpSocket->errorString());
	}
}
