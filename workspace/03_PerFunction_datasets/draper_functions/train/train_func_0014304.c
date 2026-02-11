CompareDateTime ( const XMP_DateTime & _in_left,
							const XMP_DateTime & _in_right )
{
	int result;

	XMP_DateTime left  = _in_left;
	XMP_DateTime right = _in_right;

	ConvertToUTCTime ( &left );
	ConvertToUTCTime ( &right );


	if ( left.year < right.year ) {
		result = -1;
	} else if ( left.year > right.year ) {
		result = +1;
	} else if ( left.month < right.month ) {
		result = -1;
	} else if ( left.month > right.month ) {
		result = +1;
	} else if ( left.day < right.day ) {
		result = -1;
	} else if ( left.day > right.day ) {
		result = +1;
	} else if ( left.hour < right.hour ) {
		result = -1;
	} else if ( left.hour > right.hour ) {
		result = +1;
	} else if ( left.minute < right.minute ) {
		result = -1;
	} else if ( left.minute > right.minute ) {
		result = +1;
	} else if ( left.second < right.second ) {
		result = -1;
	} else if ( left.second > right.second ) {
		result = +1;
	} else if ( left.nanoSecond < right.nanoSecond ) {
		result = -1;
	} else if ( left.nanoSecond > right.nanoSecond ) {
		result = +1;
	} else {
		result = 0;
	}

	return result;

}
