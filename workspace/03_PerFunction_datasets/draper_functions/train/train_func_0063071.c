next_iteration(t_iterator *iter)
{
    t_iterator *this_iter;
    TBOOLEAN condition = FALSE;

    if (!iter || iter->empty_iteration)
	return FALSE;


    this_iter = iter->prev;

    if (!this_iter)
	return FALSE;

    while (!iter->really_done && this_iter != iter && this_iter->done) {
	this_iter->iteration_current = this_iter->iteration_start;
	this_iter->done = FALSE;
	if (this_iter->iteration_string) {
	    free(this_iter->iteration_udv->udv_value.v.string_val);
	    this_iter->iteration_udv->udv_value.v.string_val
	         = gp_word(this_iter->iteration_string, this_iter->iteration_current);
    } else
	    this_iter->iteration_udv->udv_value.v.int_val = this_iter->iteration_current;

	this_iter = this_iter->prev;
    }

    if (!this_iter->iteration_udv) {
	this_iter->iteration = 0;
	return FALSE;
    }
    iter->iteration++;

    if (!iter->really_done)
	this_iter->iteration_current += this_iter->iteration_increment;
    if (this_iter->iteration_string) {
	free(this_iter->iteration_udv->udv_value.v.string_val);
	this_iter->iteration_udv->udv_value.v.string_val
	    = gp_word(this_iter->iteration_string, this_iter->iteration_current);
    } else
	this_iter->iteration_udv->udv_value.v.int_val = this_iter->iteration_current;


    this_iter->done =
	!((this_iter->iteration_end - this_iter->iteration_current - this_iter->iteration_increment)
	   * this_iter->iteration_increment >= 0);


    this_iter = iter;
    while (this_iter) {
	condition = condition || (!this_iter->done);
	this_iter = this_iter->next;
    }
    if (!condition) {
	if (!iter->really_done) {
	    iter->really_done = TRUE;
	    condition = TRUE;
	} else
	    condition = FALSE;
    }
    return condition;
}
