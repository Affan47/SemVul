set(int symbol, const char *text)
{
	if(check_symbol(symbol) < 0)
		return;
	switch(table[symbol]->typecode)
	{
	  case CFG_NONE:
		return;
	  case CFG_BOOL:
		{


			char buf[16];
			strncpy(buf, text, 15);
			for(int i = 0; i < 15; ++i)
				buf[i] = tolower(buf[i]);
			cfg_switch_t *k = (cfg_switch_t *)table[symbol];
			if( strncmp(buf, "yes", 3) || strncmp(buf, "true", 4) ||
					strcmp(buf, "on") || strncmp(buf, "enable", 6) ||
					strncmp(buf, "activ", 5) ||
					strcmp(buf, "one") || strcmp(buf, "1") )
				*(k->value) = 1;
			else
				*(k->value) = 0;
		}
		break;
	  case CFG_INT:
		{
			cfg_key_int_t *k = (cfg_key_int_t *)table[symbol];
			*(k->value) = atoi(text);
		}
		break;
	  case CFG_FLOAT:
		{
			cfg_key_float_t *k = (cfg_key_float_t *)table[symbol];
			*(k->value) = atof(text);
		}
		break;
	  case CFG_STRING:
		{
			cfg_key_string_t *k = (cfg_key_string_t *)table[symbol];
			strncpy(*(k->value), text, CFG_STRING_LENGTH-1);
			*(k->value)[CFG_STRING_LENGTH-1] = 0;
		}
		break;
	}
	table[symbol]->redefined = 1;
}
