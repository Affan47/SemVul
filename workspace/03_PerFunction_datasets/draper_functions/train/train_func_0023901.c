tls_resultsReady()
	{
		QCA_logTextMessage(QString("tls[%1]: c->resultsReady()").arg(q->objectName()), Logger::Information);

		Q_ASSERT(op != -1);

		int last_op = op;
		op = -1;

		if(last_op == OpStart)
			start_finished();
		else
			update_finished();
	}
