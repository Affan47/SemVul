success(std::string message)
{
	try {
		if (mboxAccount.isDestroyed())
		{
			fail("Operation aborted.");
			return;
		}

		mboxAccount->genericReadMessageContent(&*mboxAccount,
						       &*mboxAccount,
						       messages,
						       peek,
						       readType,
						       callback);
		delete this;
	} catch (...) {
		fail("An exception occured in mbox::MultiLockGenericAttributes");
	}
}
