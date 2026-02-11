combine_linedesc(linedesc *desc, linedesc* elem) {
    if ( elem->ld != def ) {
	desc->ld = elem->ld;
	desc->param = elem->param;
    }
    if ( elem->fill ) desc->fill = elem->fill;
    if ( elem->thick ) desc->thick = elem->thick;
    if ( elem->color ) {
	if ( desc->color ) delete desc->color;
	desc->color = elem->color;

	elem->color = 0;
    }
    if ( elem->fillcolor ) {
	if ( desc->fillcolor ) delete desc->fillcolor;
	desc->fillcolor = elem->fillcolor;


	elem->fillcolor = 0;
    }
    delete elem;
    return desc;
}
