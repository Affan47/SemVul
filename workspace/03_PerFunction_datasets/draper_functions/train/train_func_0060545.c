Parse(const Data &entry_packet)
{
	uint32_t count = 0;

	size_t size = entry_packet.GetSize();

	while (count < size) {
		uint16_t len = 0;

		const unsigned char *ptr = (entry_packet.GetData() + count);
		Protocol::JVMModulesEntry *e = (Protocol::JVMModulesEntry *) ptr;

		len = SB_JVMMODULES_ENTRY_HEADER_SIZE + be_btohs(e->sizename);
		if( (count + len) > size )
			break;

		JVMModulesEntry entry;

		entry.Id = be_btohl(e->id);
		entry.UniqueID = be_btohl(e->uniqueId);
		(entry.Name).assign((char *) (ptr + SB_JVMMODULES_ENTRY_HEADER_SIZE), be_btohs(e->sizename));

		push_back(entry);

		count += len;
	}
}
