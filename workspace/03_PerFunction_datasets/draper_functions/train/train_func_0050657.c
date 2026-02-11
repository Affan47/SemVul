checkCondition(const char* condition, int num)
{
	const char* b = condition;


	int onlySpaces = 1;

	while (*b)
	{
		if (*b != ' ')
		{
			onlySpaces = 0;
			break;
		}

		++b;
	}


	if (*condition && !onlySpaces)
	{
		Condition* c = generateCondition(condition);


		if (watchpoint[num].cond)
		{
			freeTree(watchpoint[num].cond);
			free(watchpoint[num].condText);
			watchpoint[num].cond = 0;
			watchpoint[num].condText = 0;
		}


		if (c)
		{
			watchpoint[num].cond = c;
			watchpoint[num].condText = (char*)malloc(strlen(condition) + 1);
            if (!watchpoint[num].condText)
                return 0;
			strcpy(watchpoint[num].condText, condition);
		}
		else
		{
			watchpoint[num].cond = 0;
		}

		return watchpoint[num].cond == 0 ? 2 : 0;
	}
	else
	{

		if (watchpoint[num].cond)
		{
			freeTree(watchpoint[num].cond);
			free(watchpoint[num].condText);
			watchpoint[num].cond = 0;
			watchpoint[num].condText = 0;
		}
		return 0;
	}
}
