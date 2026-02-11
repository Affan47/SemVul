DataAvailable(ConnectionID Connection, void *Data, unsigned short DataLength,
		   unsigned short DataHandle, int *DiscardData) {
	if (MainDataAvailable_p)
		MainDataAvailable_p(Connection, Data, DataLength, DataHandle,
				    DiscardData);
	else
		*DiscardData = TRUE;
}
