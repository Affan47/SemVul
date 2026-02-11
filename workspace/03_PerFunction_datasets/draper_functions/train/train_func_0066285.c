gnc_quickfill_cell_add_completion (QuickFillCell *cell, const char *completion)
{
    if (cell == NULL)
        return;

    gnc_quickfill_insert (cell->qf, completion, cell->sort);
}
