ReadRangeFromString(char *SearchString, const char *StartIndicationString, const char *EndIndicationString, int *min, int *max, int default_val)
{
	char *ptr;
	int return_value = 0;


	char *search_ptr = ReadAndMallocStringFromDataOptional(SearchString, StartIndicationString, EndIndicationString);
	if (!search_ptr) {

		*min = *max = default_val;
		return 1;
	}

	*min = strtol(search_ptr, &ptr, 10);
	if (*ptr == '-') {
		ptr++;
		*max = strtol(ptr, NULL, 10);
	} else {
		*max = *min;
	}


	if (*min < 0) {
		ErrorMessage(__FUNCTION__, "\
The value read in as a minimum (%d) is a negative number.\n\
This most likely means corrupted data.\n\
Setting both the maximum and minimum to the default value (%d).", NO_NEED_TO_INFORM, IS_WARNING_ONLY, *min, default_val);
		*min = *max = default_val;
		return_value = 2;
	} else if (*max < *min) {
		ErrorMessage(__FUNCTION__, "\
The value read in as a maximum (%d) is less than the minimum (%d).\n\
This most likely means corrupted data.\n\
Setting both the maximum and minimum to the default value (%d).", NO_NEED_TO_INFORM, IS_WARNING_ONLY, *max, *min, default_val);
		*min = *max = default_val;
		return_value = 2;
	}

	free(search_ptr);
	return return_value;
}
