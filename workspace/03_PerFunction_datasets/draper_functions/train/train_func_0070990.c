free_tabu(tabu_list *tabu,unsigned int name)
{
	if(tabu->name==name)
	{
		return;
	}
	else{
		free_tabu(tabu->next,name);
		free((char *)tabu);
	}
}
