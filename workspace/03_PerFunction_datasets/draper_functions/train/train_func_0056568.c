itemWritten(int id, int)
{
	if(id == TypeStanza) {
		--stanzasPending;
		++stanzasWritten;
	}
}
