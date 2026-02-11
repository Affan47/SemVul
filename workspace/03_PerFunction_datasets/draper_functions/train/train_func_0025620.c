tagvlentypes(Symbol* tsym)
{
    int tagged = 0;
    int j;
    switch (tsym->subclass) {
        case NC_VLEN:
	    tagged = 1;
	    tagvlentypes(tsym->typ.basetype);
	    break;
	case NC_COMPOUND:
	    for(j=0;j<listlength(tsym->subnodes);j++) {
		Symbol* field = (Symbol*)listget(tsym->subnodes,j);
		ASSERT(field->subclass == NC_FIELD);
		if(tagvlentypes(field->typ.basetype)) tagged = 1;
	    }
	    break;
	default: break;
    }
    if(tagged) tsym->typ.hasvlen = 1;
    return tagged;
}
