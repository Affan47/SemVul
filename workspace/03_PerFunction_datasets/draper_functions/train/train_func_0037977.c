EngineStatus(const std::string &msg, bool error, bool slowsync)
{
	if( error )
		cout << _C("ERROR: ");
	cout << msg << endl;
}
