set_gains_date_dirty (Transaction *trans)
{
    FOR_EACH_SPLIT(trans, s->gains |= GAINS_STATUS_DATE_DIRTY);
}
