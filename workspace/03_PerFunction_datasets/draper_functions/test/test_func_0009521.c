ta_mark_all(TA_S *f_line)
{
    TA_S *ctmp;
    int   how_many_selected = 0;

    for(ctmp = f_line; ctmp; ctmp = next_sel_taline(ctmp)){
	ctmp->checked = 1;
	how_many_selected++;
    }

    return(how_many_selected);
}
