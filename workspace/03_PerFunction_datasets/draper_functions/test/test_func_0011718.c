create_PT_bond()
	{
	PT_bond *THIS			= (PT_bond *)calloc(sizeof(PT_bond), 1);
	if(!THIS){ aisc_server_error = "Malloc error in create_PT_bond !"; return 0;}
	THIS->val			= 0.0;
	return THIS; }
