N_compute_gradient_field_components_2d(N_gradient_field_2d * field,
				       N_array_2d * x_comp,
				       N_array_2d * y_comp)
{
    int i, j;
    int rows, cols;
    double vx, vy;
    N_array_2d *x = x_comp;
    N_array_2d *y = y_comp;
    N_gradient_2d grad;


    if (!x)
	G_fatal_error("N_compute_gradient_components_2d: x array is empty");
    if (!y)
	G_fatal_error("N_compute_gradient_components_2d: y array is empty");

    cols = field->x_array->cols;
    rows = field->x_array->rows;


    if (x->cols != cols || x->rows != rows)
	G_fatal_error
	    ("N_compute_gradient_components_2d: the size of the x array doesn't fit the gradient field size");
    if (y->cols != cols || y->rows != rows)
	G_fatal_error
	    ("N_compute_gradient_components_2d: the size of the y array doesn't fit the gradient field size");

    for (j = 0; j < rows; j++)
	for (i = 0; i < cols; i++) {
	    N_get_gradient_2d(field, &grad, i, j);


	    if (grad.WC == 0.0 || grad.EC == 0.0)
		vx = (grad.WC + grad.EC);
	    else
		vx = (grad.WC + grad.EC) / 2;
	    if (grad.NC == 0.0 || grad.SC == 0.0)
		vy = (grad.NC + grad.SC);
	    else
		vy = (grad.NC + grad.SC) / 2;

	    N_put_array_2d_d_value(x, i, j, vx);
	    N_put_array_2d_d_value(y, i, j, vy);
	}

    return;
}
