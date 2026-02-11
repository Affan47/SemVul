setUp(void)
{
	this->formatter = new UnitTestMockResultFormater();
	this->listener = new svutListenerDirectOutputter(*this->formatter);
	this->ref = new UnitTestMockResultFormater();
}
