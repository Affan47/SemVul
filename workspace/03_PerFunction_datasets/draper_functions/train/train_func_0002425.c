tick()
{
    if (mouseDisabled) {
        return;
    }


    if (paintEditObj || paintAltObj) {

        int i, j;
        emit getMousePos (i, j);


        if ((i != oldI) || (j != oldJ)) {

            insertEditObj (i, j, (paintEditObj) ? editObj : FREE);
            oldI = i;
            oldJ = j;
        }
    }
}
