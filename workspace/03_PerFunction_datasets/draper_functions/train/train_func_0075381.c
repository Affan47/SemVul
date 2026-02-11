get_pair2(chasen_cell_t * cell, rensetu_pair2_t * pair)
{
    chasen_cell_t *cell_p;
    char *s;

    pair->hinsi = NULL;
    pair->type = 0;
    pair->form = NULL;
    pair->goi = NULL;

    if (nullp(cell_p = cha_car(cell)))
	return;

    s = cha_s_atom(cha_car(cell_p));
    if (cha_litmatch(s, 2, STR_BOS, STR_EOS)) {
	pair->hinsi = NULL;
	return;
    }
    pair->hinsi = cell_p;

    if (nullp(cell_p = cha_car(cell = cha_cdr(cell))))
	return;
    pair->type = cha_get_type_id(cha_s_atom(cell_p));

    if (nullp(cell_p = cha_car(cell = cha_cdr(cell))))
	return;

    if (strcmp(s = cha_s_atom(cell_p), "*"))
	pair->form = cha_strdup(s);

    if (nullp(cell_p = cha_car(cell = cha_cdr(cell))))
	return;
    pair->goi = cha_strdup(cha_s_atom(cell_p));
}
