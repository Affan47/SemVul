SHA1Finalize(SHA1Context * context, uint8_t Pad_Byte)
{
	int i;
	SHA1PadMessage(context, Pad_Byte);

	for (i = 0; i < SHA1_Message_Block_Size; ++i) {
		context->Message_Block[i] = 0;
	}
	context->Length_High = 0;
	context->Length_Low = 0;
	context->Computed = 1;
}
