BeginUniqueSerialize(SerializationContext *context, RakNetGUID _guid, BitStream *_bitStream)
{
	RakAssert(_guid!=UNASSIGNED_RAKNET_GUID);
	context->anyVariablesWritten=false;
	context->guid=_guid;
	context->bitStream=_bitStream;
	if (context->variableHistoryUnique==0)
		context->variableHistoryUnique=StartVariableHistoryWrite(_guid);
	context->variableHistory=context->variableHistoryUnique;
	context->newSystemSend=false;

	context->serializationMode=RELIABLE;
}
