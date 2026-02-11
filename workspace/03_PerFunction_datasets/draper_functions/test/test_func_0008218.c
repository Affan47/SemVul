setNewSearch(ED4_SearchPositionType type)
{
    if (type==ED4_ANY_PATTERN) {
        int i;
        for (i=0; i<SEARCH_PATTERNS; i++) {
            setNewSearch(ED4_SearchPositionType(i));
        }
    }
    else {
        int next_unused_stamp = timeOfLastSearch[type] + 1;

        shown[type] = resultsAreShown(type);
        if (timeOfNextSearch[type]!=next_unused_stamp) {
            timeOfNextSearch[type] = next_unused_stamp;
        }
    }
}
