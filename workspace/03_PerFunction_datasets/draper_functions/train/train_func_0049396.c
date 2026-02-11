deviceNonlinearGetVariable(char *name, device_ *r)
{
	devicePrivate_ *p;
	variable_ *variable;
	double **ptr;

	ReturnNULLIf(r == NULL);
	p = r->private;
	ReturnNULLIf(p == NULL);

	if(!strcmp("time", name)) {
		p->time = &r->control->time;
		ptr = &p->time;
	} else if(((name[0] == 'i') || (name[0] == 'v')) && name[1] == '(') {


		variable = calloc(1, sizeof(variable_));
		ReturnNULLIf(variable == NULL);


		variable->row = matrixFindOrAddRow(r->matrix, 0x0, name);
		ReturnNULLIf(variable->row == NULL);

		variable->nodeRX = matrixFindOrAddNode(r->matrix, p->rowR,
				variable->row);
		ReturnNULLIf(variable->nodeRX == NULL);

		variable->name = name;
		ReturnNULLIf(listAdd(p->variables, variable, NULL));


		ptr = rowGetSolutionPtr(variable->row);
		ReturnNULLIf(ptr == NULL);
	} else {
		ReturnNULL("For the B element, included varaibles must be in the form"
			" i(...), v(...), or time -- not %s", name);
	}

	return ptr;
}
