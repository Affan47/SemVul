is_sets(RegExpNode *p)
{
Buffer	buf;
int	c=curchar();
int	call_parsechar=1;

	if (c == ':')
	{
		do
		{
			buf += c;
			nextchar();
		} while ( (c=curchar()) >= 0 && isalpha(c));

		if (c == ':')
		{
			buf += c;
			nextchar();
			c=curchar();
			if (c == ']')
			{
				buf += '\0';

			const char *q=(const char *)buf;
			unsigned i;

				for (i=0; i<sizeof(is_setname)/
					sizeof(is_setname[0]); i++)
				{
					if (strcmp(is_setname[i], q) == 0)
					{
						(*is_setfunc[i])(p->reset);
						return;
					}
				}
			}
		}

	int	i=0;

		for (i=0; i<buf.Length(); i++)
		{
			c=(int)(unsigned char)((const char*)buf)[i];
			p->reset[ c / 8 ] |= 1 << (c % 8);
		}


		call_parsechar=0;
		if (curchar() == ']')	return;
	}

	do
	{
	int	c2;

		if (c == 0)	throw -1;

		if (c == '.')
		{
			for (c2=0; c2 < 256/8; c2++)
				if (c2 != '\n' / 8)
					p->reset[c2]= ~0;
				else
					p->reset[c2] |= ~(1 << ('\n' % 8));
			if (call_parsechar)
				nextchar();
			call_parsechar=1;
			continue;
		}
		if (call_parsechar)
			c=parsechar();
		c2=c;
		call_parsechar=1;

		if (curchar() == '-')
		{
			nextchar();
			c2=parsechar();
		}
		while ( c <= c2 )
		{
			p->reset[ c / 8 ] |= 1 << (c % 8);
			++c;
		}
	} while ((c=curchar()) != ']');
}
