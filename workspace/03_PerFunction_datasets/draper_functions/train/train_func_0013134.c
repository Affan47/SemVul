OnReceive(Packet *packet)
{
	if (packet->data[0]==ID_RELAY_PLUGIN)
	{
		switch (packet->data[1])
		{
		case RPE_MESSAGE_TO_SERVER_FROM_CLIENT:
			{
				BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(MessageID)*2);
				PacketPriority priority;
				PacketReliability reliability;
				char orderingChannel;
				unsigned char cIn;
				bsIn.Read(cIn);
				priority = (PacketPriority) cIn;
				bsIn.Read(cIn);
				reliability = (PacketReliability) cIn;
				bsIn.Read(orderingChannel);
				RakString key;
				bsIn.ReadCompressed(key);
				BitStream bsData;
				bsIn.Read(&bsData);
				StrAndGuidAndRoom **strAndGuid = strToGuidHash.Peek(key);
				StrAndGuidAndRoom **strAndGuidSender = guidToStrHash.Peek(packet->guid);
				if (strAndGuid && strAndGuidSender)
				{
					BitStream bsOut;
					bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
					bsOut.WriteCasted<MessageID>(RPE_MESSAGE_TO_CLIENT_FROM_SERVER);
					bsOut.WriteCompressed( (*strAndGuidSender)->str );
					bsOut.AlignWriteToByteBoundary();
					bsOut.Write(bsData);
					SendUnified(&bsOut, priority, reliability, orderingChannel, (*strAndGuid)->guid, false);
				}

				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}

		case RPE_ADD_CLIENT_REQUEST_FROM_CLIENT:
			{
				BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(MessageID)*2);
				RakString key;
				bsIn.ReadCompressed(key);
				BitStream bsOut;
				bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
				if (acceptAddParticipantRequests)
					bsOut.WriteCasted<MessageID>(AddParticipantOnServer(key, packet->guid));
				else
					bsOut.WriteCasted<MessageID>(RPE_ADD_CLIENT_NOT_ALLOWED);
				bsOut.WriteCompressed(key);
				SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		case RPE_REMOVE_CLIENT_REQUEST_FROM_CLIENT:
			{
				RemoveParticipantOnServer(packet->guid);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_GROUP_MESSAGE_FROM_CLIENT:
			{
				OnGroupMessageFromClient(packet);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_JOIN_GROUP_REQUEST_FROM_CLIENT:
			{
				OnJoinGroupRequestFromClient(packet);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_LEAVE_GROUP_REQUEST_FROM_CLIENT:
			{
				OnLeaveGroupRequestFromClient(packet);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		case RPE_GET_GROUP_LIST_REQUEST_FROM_CLIENT:
			{
				SendChatRoomsList(packet->guid);
			}
			return RR_STOP_PROCESSING_AND_DEALLOCATE;
		}

	}

	return RR_CONTINUE_PROCESSING;
}
