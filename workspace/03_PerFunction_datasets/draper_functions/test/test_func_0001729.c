CORD_pos_fetch(register CORD_pos p)
{
    if (p[0].cur_start <= p[0].cur_pos && p[0].cur_pos < p[0].cur_end) {
    	return(p[0].cur_leaf[p[0].cur_pos - p[0].cur_start]);
    } else {
        return(CORD__pos_fetch(p));
    }
}
