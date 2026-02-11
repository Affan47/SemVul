parser(){
	global.symTable->Top = NULL;

	D("PARSER START");
	struct astNode* prog = parseProgram();
	if(!prog){
		return False;
	}


	checkFunctionDeclarations(global.funcTable);

	global.globalTable = NULL;

	global.program = prog;
	return True;
}
