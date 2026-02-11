DCH_processor(FormatNode *node, char *inout, bool is_to_char,
			  bool is_interval, void *data)
{
	FormatNode *n;
	char	   *s;


	DCH_global_fx = false;

	for (n = node, s = inout; n->type != NODE_TYPE_END; n++)
	{
		if (!is_to_char && *s == '\0')


			break;

		if (n->type == NODE_TYPE_ACTION)
		{
			int			len;


			len = n->key->action(n->key->id, s, n->suffix, is_to_char,
								 is_interval, n, data);
			if (len > 0)
				s += len - 1;
			else if (len == -1)
				continue;
		}
		else
		{


			if (is_to_char)
				*s = n->character;
			else
			{


				if (isspace((unsigned char) n->character) && !DCH_global_fx)
					while (*s != '\0' && isspace((unsigned char) *(s + 1)))
						++s;
			}
		}
		++s;
	}

	if (is_to_char)
		*s = '\0';
	return inout;
}
