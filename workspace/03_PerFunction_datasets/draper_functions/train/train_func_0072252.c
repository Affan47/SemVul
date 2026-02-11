blank_keymenu(int row, int column)
{
    struct variable *vars = ps_global->vars;
    COLOR_PAIR *lastc;

    if(FOOTER_ROWS(ps_global) > 1){
	km_state.blanked    = 1;
	km_state.row        = row;
	km_state.column     = column;
	MoveCursor(row, column);
	lastc = pico_set_colors(VAR_KEYLABEL_FORE_COLOR,
				VAR_KEYLABEL_BACK_COLOR, PSC_NORM|PSC_RET);

	CleartoEOLN();
	MoveCursor(row+1, column);
	CleartoEOLN();
	fflush(stdout);
	if(lastc){
	    (void)pico_set_colorp(lastc, PSC_NONE);
	    free_color_pair(&lastc);
	}
    }
}
