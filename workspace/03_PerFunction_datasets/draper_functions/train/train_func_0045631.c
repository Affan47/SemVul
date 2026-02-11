setUp(void )
{
	obj = new MockTestCaseForCapture;
	out = new stringstream;
	formatter = new svutResultFormatterStdBW(*out);
	listener = new svutListenerDirectOutputter(*formatter);
}
