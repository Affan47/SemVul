testWaitDequeue()
{
	TimedNotificationQueue queue;

	Poco::Timestamp ts1;
	ts1 += 100000;
	Poco::Timestamp ts2;
	ts2 += 200000;
	Poco::Timestamp ts3;
	ts3 += 300000;
	Poco::Timestamp ts4;
	ts4 += 400000;

	queue.enqueueNotification(new QTestNotification("first"), ts1);
	queue.enqueueNotification(new QTestNotification("fourth"), ts4);
	queue.enqueueNotification(new QTestNotification("third"), ts3);
	queue.enqueueNotification(new QTestNotification("second"), ts2);
	assert (!queue.empty());
	assert (queue.size() == 4);
	QTestNotification* pTNf = dynamic_cast<QTestNotification*>(queue.waitDequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "first");
	pTNf->release();
	assert (ts1.elapsed() >= 0);
	assert (!queue.empty());
	assert (queue.size() == 3);

	pTNf = dynamic_cast<QTestNotification*>(queue.waitDequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "second");
	pTNf->release();
	assert (ts2.elapsed() >= 0);
	assert (!queue.empty());
	assert (queue.size() == 2);

	pTNf = dynamic_cast<QTestNotification*>(queue.waitDequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "third");
	pTNf->release();
	assert (ts3.elapsed() >= 0);
	assert (!queue.empty());
	assert (queue.size() == 1);

	pTNf = dynamic_cast<QTestNotification*>(queue.waitDequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "fourth");
	pTNf->release();
	assert (ts4.elapsed() >= 0);
	assert (queue.empty());
	assert (queue.size() == 0);
}
