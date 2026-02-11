success(std::string message)
{
	try {
		if (mboxAccount.isDestroyed())
		{
			fail("Operation aborted.");
			return;
		}

		mboxAccount->genericAttributes(&*mboxAccount,
					       &*mboxAccount,
					       messages,
					       attributes,
					       callback);
		delete this;
	} catch (...) {
		fail("An exception occured in mbox::MultiLockGenericAttributes");
	}
}
