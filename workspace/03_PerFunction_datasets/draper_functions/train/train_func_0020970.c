SplitPacket(char* packet, char* argv[])
		{


			char* ptrToArgument = StringSplit::Run(packet, " ");


			uint8_t argCount = 0;

			while(ptrToArgument != 0)
			{

				argv[argCount] = ptrToArgument;


				ptrToArgument = StringSplit::Run(0, " ");
				argCount++;
			}


			return argCount;
		}
