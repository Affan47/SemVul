GetRegisteredCommand(const char *command, RegisteredCommand *rc)
{
	bool objectExists;
	unsigned index;
	index=commandList.GetIndexFromKey(command, &objectExists);
	if (objectExists)
		*rc=commandList[index];
	return objectExists;
}
