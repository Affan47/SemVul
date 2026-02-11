lt_set_initial_value(struct lt_trace *lt, char value)
{
if(lt)
	{
	int tag;
	switch(value)
		{
		case '0':	tag = 0; break;
		case '1':	tag = 1; break;
		case 'Z':
		case 'z':	tag = 2; break;
		case 'X':
		case 'x':	tag = 3; break;
		case 'H':
		case 'h':	tag = 4; break;
		case 'U':
		case 'u':	tag = 5; break;
		case 'W':
		case 'w':	tag = 6; break;
		case 'L':
		case 'l':	tag = 0x7; break;
		case '-':	tag = 0x8; break;
		default:	tag = -1;  break;
		}
	lt->initial_value = tag;
	}
}
