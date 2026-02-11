DefaultOneOption(int id)
{
	switch (id)
	{
		case OPT_SET_COLUMNS:
		case OPT_ADD_COLUMNS:
		case OPT_REMOVE_COLUMNS:
			DefaultColumns();
			break;

		case OPT_SEPARATION:
			separation = 2;
			break;

		case OPT_WIDTH:
			outputWidth = DEFAULT_WIDTH;
			break;

		case OPT_SLEEP_TIME:
			sleepTimeMs = DEFAULT_SLEEP_SEC * 1000;
			break;

		case OPT_INFO:
			isInfoShown = FALSE;
			break;

		case OPT_NO_SELF:
			noSelf = FALSE;
			break;

		case OPT_MY_PROCS:
			myProcs = FALSE;
			break;

		case OPT_SHOW_THREADS:
			showThreads = FALSE;
			break;

		case OPT_USE_THREADS:
			useThreads = FALSE;
			break;

		case OPT_NO_COPY:
			noCopy = FALSE;

		case OPT_ACTIVE_ONLY:
			activeOnly = FALSE;
			break;

		case OPT_NO_ROOT:
			noRoot = FALSE;
			break;

		case OPT_CLEAR_SCREEN:
			clearScreen = FALSE;
			break;

		case OPT_NORMAL_SORT:
		case OPT_REVERSE_SORT:
		case OPT_NORMAL_SORT_EXPR:
		case OPT_REVERSE_SORT_EXPR:
		case OPT_NO_SORT:
			ClearSorting();
			break;

		case OPT_LOOP:
			isLooping = FALSE;
			break;

		case OPT_VERTICAL:
			isVertical = FALSE;
			break;

		case OPT_INIT_TIME:
			initSleepTime = DEFAULT_INIT_SEC;
			break;

		case OPT_CONDITION:
			ClearCondition();
			break;

		case OPT_TOP_COUNT:
			topCount = 0;
			break;

		case OPT_NO_HEADER:
			noHeader = FALSE;
			break;

		case OPT_PIDS:
			pidCount = 0;
			break;

		case OPT_USERS:
			userCount = 0;
			break;

		case OPT_GROUPS:
			groupCount = 0;
			break;

		case OPT_PROGRAMS:
			programCount = 0;
			break;

		case OPT_ACTIVE_TIME:
			activeTime = DEFAULT_ACTIVE_SEC;
			break;

		case OPT_DEATH_TIME:
			deathTime = DEFAULT_DEATH_SEC;
			break;

		case OPT_SYNC_TIME:
			syncTime = DEFAULT_SYNC_SEC;
			break;

		case OPT_COLUMN_WIDTH:
			DefaultColumnWidths();
			break;

		case OPT_GEOMETRY:
			ReplaceString(&geometry, DEFAULT_GEOMETRY);
			break;

		case OPT_FONT:
			ReplaceString(&fontName, DEFAULT_FONT);
			break;

		case OPT_FOREGROUND:
			ReplaceString(&foregroundName, DEFAULT_FOREGROUND);
			break;

		case OPT_BACKGROUND:
			ReplaceString(&backgroundName, DEFAULT_BACKGROUND);
			break;

		case OPT_DISPLAY:
			ReplaceString(&displayName, NULL);
			break;

		case OPT_PERCENT_SECONDS:
			percentSeconds = PERCENT_DEFAULT_SECONDS;
			break;

		case OPT_SCROLL_TIME:
			scrollSeconds = DEFAULT_SCROLL_SEC;
			break;

		case OPT_OVERLAP_LINES:
			overlapLines = DEFAULT_OVERLAP_LINES;
			break;

		case OPT_INFO_COLOR:
			infoColorId = DEFAULT_COLOR_ID;
			break;

		case OPT_HEADER_COLOR:
			headerColorId = DEFAULT_COLOR_ID;
			break;

		case OPT_ROW_COLOR:
			ClearRowColorConditions();
			break;

		default:
			break;
	}
}
