lt_emit_value_string(struct lt_trace *lt, struct lt_symbol *s, unsigned int row, char *value)
{
int rc=0;
int start_position;
int tag;

if((!lt)||(!s)||(!value)) return(rc);

while(s->aliased_to)
	{
	s=s->aliased_to;
	}

if((s->flags)&LT_SYM_F_STRING)
	{
	int numbytes;
	unsigned int last_change_delta = lt->position - s->last_change - 2;

	if(last_change_delta >= 256*65536)
		{
		numbytes = 3;
		}
	else
	if(last_change_delta >= 65536)
		{
		numbytes = 2;
		}
	else
	if(last_change_delta >= 256)
		{
		numbytes = 1;
		}
	else
		{
		numbytes = 0;
		}

	start_position = lt->position;
	tag = (numbytes<<4);
	lt_emit_u8(lt, tag);
	switch(numbytes&3)
		{
		case 0: lt_emit_u8(lt, last_change_delta); break;
		case 1: lt_emit_u16(lt, last_change_delta); break;
		case 2: lt_emit_u24(lt, last_change_delta); break;
		case 3: lt_emit_u32(lt, last_change_delta); break;
		}

	s->last_change = start_position;

	if(s->rows>0)
		{
		if(s->rows >= 256*65536)
			{
			numbytes = 3;
			}
		else
		if(s->rows >= 65536)
			{
			numbytes = 2;
			}
		else
		if(s->rows >= 256)
			{
			numbytes = 1;
			}
		else
			{
			numbytes = 0;
			}

		switch(numbytes&3)
			{
			case 0: lt_emit_u8(lt, row); break;
			case 1: lt_emit_u16(lt, row); break;
			case 2: lt_emit_u24(lt, row); break;
			case 3: lt_emit_u32(lt, row); break;
			}
		}

	rc=lt_emit_string(lt, value);

	if(lt->timebuff)
		{
		lt->timechangecount++;
		if(lt->timecurr)
			{
			lt->timecurr->next = lt->timebuff;
			lt->timecurr = lt->timebuff;
			}
			else
			{
			lt->timehead = lt->timecurr = lt->timebuff;
			}

		lt->timebuff=NULL;
		}
	}

return(rc);
}
