writeValue(SoOutput *out) const


{
    int	i;

    if (out->isBinary()) {
	out->write(num);
        writeBinaryValues(out);
    }

    else {
	if (num == 1)
	    write1Value(out, 0);

	else {
	    int	numOnLine = 0, maxOnLine = getNumValuesPerLine();

	    out->write(OPEN_BRACE_CHAR);
	    out->write(' ');

	    out->incrementIndent(4);

	    for (i = 0; i < num; i++) {

		write1Value(out, i);

		if (i < num - 1) {
		    out->write(VALUE_SEPARATOR_CHAR);
		    if (++numOnLine == maxOnLine && ! out->isCompact()) {
			out->write('\n');
			out->indent();
			out->write(' ');
			out->write(' ');
			numOnLine = 0;
		    }
		    else
			out->write(' ');
		}
	    }

	    out->write(' ');
	    out->write(CLOSE_BRACE_CHAR);

	    out->decrementIndent(4);
	}
    }
}
