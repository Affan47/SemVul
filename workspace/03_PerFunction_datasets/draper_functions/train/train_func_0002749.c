AdjustTimings(uint32 ppqn)
{
	uint32		tempo = 500000;
	uint32		time_prev = 0;
	uint32		hs_rem = 0;
	uint32		hs     = 0;

	ppqn *= 10000;


	NoteStack notes;

	for (midi_event	*event = list; event; event = event->next) {


			uint64 aim = event->time - time_prev;
			aim *= tempo;

			hs_rem += aim%ppqn;
			hs += aim/ppqn;
			hs += hs_rem/ppqn;
			hs_rem %= ppqn;

			time_prev = event->time;
			event->time = (hs*6)/5 + (6*hs_rem)/(5*ppqn);


			if (event->status <= 0x9F) {


				if ((event->status>>4) == MIDI_STATUS_NOTE_ON && event->data[1])
					notes.Push(event);
				else {
					midi_event *prev = notes.FindAndPop(event);
					if (prev) prev->duration = event->time - prev->time;
				}

			}
			else if (event->status == 0xFF && event->data[0] == 0x51) {

				tempo = (event->buffer[0] << 16) +
					(event->buffer[1] << 8) +
					event->buffer[2];

				event->buffer[0] = 0x07;
				event->buffer[1] = 0xA1;
				event->buffer[2] = 0x20;
			}
	}


	static const unsigned char tempo_buf[5] = { 0x51, 0x03, 0x07, 0xA1, 0x20 };
	BufferDataSource ds((char *)tempo_buf, 5);
	current = list;
	ConvertSystemMessage (0, 0xFF,&ds);
}
