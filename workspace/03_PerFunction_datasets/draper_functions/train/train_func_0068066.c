N_solver_gauss(N_les * les)
{

    if (les->type != N_NORMAL_LES) {
	G_warning(_("The gauss elimination solver does not work with sparse matrices"));
	return 0;
    }

    if (les->quad != 1) {
	G_fatal_error(_("The linear equation system is not quadratic"));
	return 0;
    }


    G_message(_("Starting direct gauss elimination solver"));

    N_les_pivot_create(les);
    gauss_elimination(les->A, les->b, les->rows);
    backward_solving(les->A, les->x, les->b, les->rows);

    return 1;
}
