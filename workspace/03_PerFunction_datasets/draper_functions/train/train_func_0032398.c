parseParams(){
	W("parseParams");
	struct toc* cur = NULL;
	struct queue* params = makeNewQueue();
	if(!params)
		return NULL;


	struct astNode* par = getDefPar(&cur);

	while(par != NULL){

		insertValue(&global.globalTable, par->data.str, par->dataType);


		queuePush(params, par);


		cur = getToc();
		if(cur->type == T_SCOL){

			par = getDefPar(&cur);
		}
		else if(cur->type == T_RPAR){

			break;
		}
		else {

			E("Syntax error - unsupported token in parameter definition");
			exit(synt);
		}
	}
	return params;
}
