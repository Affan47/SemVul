linear_search(char *front, char *back)
{
	while (front < back) {
		switch (compare(front, back)) {
		case EQUAL:
			return (front);
			break;
		case LESS:
			return (NULL);
			break;
		case GREATER:
			break;
		}
		SKIP_PAST_NEWLINE(front, back);
	}
	return (NULL);
}
