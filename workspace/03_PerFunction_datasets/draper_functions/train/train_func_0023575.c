CleartoEOS(void)
{
    int starting_col, starting_line;


    if(pico_usingcolor() && (!_bce || !_cleartoeos)){
	starting_col  = _col;
	starting_line = _line;
        CleartoEOLN();
	ClearLines(_line+1, _lines-1);
        MoveCursor(starting_line, starting_col);
    }
    else if(_cleartoeos)
      tputs(_cleartoeos, 1, outchar);
}
