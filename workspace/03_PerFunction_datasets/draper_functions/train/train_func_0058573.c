SHA1Input (SHA1Context * context,
	   const uint8_t * message_array, unsigned length)
{
  if (!length)
    {
      return shaSuccess;
    }

  if (!context || !message_array)
    {
      return shaNull;
    }

  if (context->Computed)
    {
      context->Corrupted = shaStateError;

      return shaStateError;
    }

  if (context->Corrupted)
    {
      return context->Corrupted;
    }
  while (length-- && !context->Corrupted)
    {
      context->Message_Block[context->Message_Block_Index++] =
	(*message_array & 0xFF);

      context->Length_Low += 8;
      if (context->Length_Low == 0)
	{
	  context->Length_High++;
	  if (context->Length_High == 0)
	    {

	      context->Corrupted = 1;
	    }
	}

      if (context->Message_Block_Index == 64)
	{
	  SHA1ProcessMessageBlock (context);
	}

      message_array++;
    }

  return shaSuccess;
}
