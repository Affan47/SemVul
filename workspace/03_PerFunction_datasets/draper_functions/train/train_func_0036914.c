selectColumns(int column) {

    bool growright = true;

    if (secondColumn == -1) {
        if (column < firstColumnSelected)
            growright = false;
        secondColumn = firstColumnSelected;
    } else if (firstColumnSelected > secondColumn) {
        growright = false;
    }

    if (growright) {
        if (column < firstColumnSelected) {


            firstColumnSelected = secondColumn;
            secondColumn = column;
        } else if (column > secondColumn) {

            secondColumn = column;
        } else {

            secondColumn = column;
        }
    } else {
        if (column < secondColumn) {

            secondColumn = column;
        } else if (column > firstColumnSelected) {


            firstColumnSelected = secondColumn;
            secondColumn = column;
        } else {

            secondColumn = column;
        }
    }

}
