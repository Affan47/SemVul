insert2Ha(struct cell_ptrHa **front_cell,
	  struct cell_ptrHa **rear_cell, float angle, int row, int col)
{
    struct cell_ptrHa *temp_cell, *temp_cell2;

    temp_cell = (struct cell_ptrHa *)(G_malloc(sizeof(struct cell_ptrHa)));

    temp_cell->angle = angle;
    temp_cell->row = row;
    temp_cell->col = col;

    if (*front_cell == NULL) {
	*front_cell = temp_cell;
	*rear_cell = temp_cell;
	temp_cell->next = NULL;
    }
    else {
	temp_cell2 = *rear_cell;
	temp_cell2->next = temp_cell;
	*rear_cell = temp_cell;
	temp_cell->next = NULL;
    }
    return;
}
