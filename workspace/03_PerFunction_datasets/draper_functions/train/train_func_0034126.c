init(void)
{
	this->ownTheFormatter = false;
	this->formatter = NULL;
	this->summary = NULL;
	this->testFilter = NULL;
	this->listener = new svutListenerMultiplexer;
}
