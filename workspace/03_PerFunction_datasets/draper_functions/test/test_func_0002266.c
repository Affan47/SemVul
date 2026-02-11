resetConnection(bool clear)
{
#ifdef BS_DEBUG
	BSDEBUG << clear;
#endif
	if(d->qsock) {
		delete d->qsock_relay;
		d->qsock_relay = 0;


			QByteArray block(d->qsock->bytesAvailable(), 0);
			d->qsock->read(block.data(), block.size());
			appendRead(block);


		d->qsock->deleteLater();
		d->qsock = 0;
	}
	else {
		if(clear)
			clearReadBuffer();
	}

	d->state = Idle;
	d->domain = "";
	d->host = "";
	d->address = QHostAddress();
	d->port = 0;
	setOpenMode(QIODevice::NotOpen);
}
