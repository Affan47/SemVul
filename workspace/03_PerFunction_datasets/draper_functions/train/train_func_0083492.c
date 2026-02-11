deleteValues(int start,
		       int numToDelete)


{
    int	lastToCopy, i;

    if (numToDelete < 0)
	numToDelete = getNum() - start;


    if (numToDelete == getNum())
	deleteAllValues();

    else {

	lastToCopy = (getNum() - 1) - numToDelete;
	for (i = start; i <= lastToCopy; i++)
	    copyValue(i, i + numToDelete);


	makeRoom(getNum() - numToDelete);
    }


    valueChanged();
}
