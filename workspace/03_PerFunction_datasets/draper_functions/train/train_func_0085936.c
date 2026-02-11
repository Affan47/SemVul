InvokeSignal(DataStructures::HashIndex functionIndex, RakNet::BitStream *serializedParameters, Packet *packet)
{
	if (functionIndex.IsInvalid())
		return;


	interruptSignal=false;
	LocalSlot *localSlot = localSlots.ItemAtIndex(functionIndex);
	unsigned int i;
	i=0;
	while (i < localSlot->slotObjects.Size())
	{


		localSlot->slotObjects[i].functionPointer(serializedParameters, packet);


		if (interruptSignal==true)
			break;

		serializedParameters->ResetReadPointer();

		i++;
	}


}
