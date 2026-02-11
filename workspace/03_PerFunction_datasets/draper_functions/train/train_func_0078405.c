statusfield_column(StatusField *field)
{
    int column;
    if (field->column >= 0)
	return (field->column > columns) ? columns : field->column;
    column = field->column +
	((status_left[field->row] + status_right[field->row] > columns) ?
	status_left[field->row] + status_right[field->row] : columns);
    return (column > columns) ? columns : column;
}
