testNullable()
{
	Nullable<int> n1;
	assert (n1.isNull());

	assert (n1.value(42) == 42);

	try
	{
		int tmp = n1.value();
		fail("null value, must throw");
	}
	catch (Poco::NullValueException&)
	{
	}

	n1 = 1;
	assert (!n1.isNull());
	assert (n1.value() == 1);

	Nullable<int> n2(42);
	assert (!n2.isNull());
	assert (n2.value() == 42);
	assert (n2.value(99) == 42);

	n1 = n2;
	assert (!n1.isNull());
	assert (n1.value() == 42);

	n1.clear();
	assert (n1.isNull());
}
