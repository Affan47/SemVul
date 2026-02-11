readValue(SoInput *in)


{
    if (in->isBinary()) {
	int	numToRead;


	if (! in->read(numToRead)) {
	    SoReadError::post(in, "Couldn't read number of binary values "
			      "in multiple-value field");
	    return FALSE;
	}


	makeRoom(numToRead);


        if (! readBinaryValues(in, numToRead))
            return FALSE;
    }

    else {
	char	c;
	int	curIndex = 0;


	if (in->read(c) && c == OPEN_BRACE_CHAR) {


	    if (in->read(c) && c == CLOSE_BRACE_CHAR)
		;

	    else {
		in->putBack(c);

		while (TRUE) {


		    if (curIndex >= getNum())
			makeRoom(getNum() + VALUE_CHUNK_SIZE);

		    if (! read1Value(in, curIndex++) || ! in->read(c)) {
			SoReadError::post(in,
					  "Couldn't read value %d of field",
					  curIndex);
			return FALSE;
		    }

		    if (c == VALUE_SEPARATOR_CHAR) {


			if (in->read(c)) {
			    if (c == CLOSE_BRACE_CHAR)
				break;
			    else
				in->putBack(c);
			}
		    }

		    else if (c == CLOSE_BRACE_CHAR)
			break;

		    else {
			SoReadError::post(in,
					  "Expected '%c' or '%c' but got "
					  "'%c' while reading value %d",
					  VALUE_SEPARATOR_CHAR,
					  CLOSE_BRACE_CHAR, c,
					  curIndex);
			return FALSE;
		    }
		}
	    }


	    if (curIndex < getNum())
		makeRoom(curIndex);
	}

	else {

	    in->putBack(c);
	    makeRoom(1);
	    if (! read1Value(in, 0))
		return FALSE;
	}
    }

    return TRUE;
}
