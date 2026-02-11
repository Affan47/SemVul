free_all_nodes(EpmdVars *g)
{
    Node *tmp;
    for(tmp=g->nodes.reg; tmp != NULL; tmp = g->nodes.reg){
	g->nodes.reg = tmp->next;
	free(tmp);
    }
    for(tmp=g->nodes.unreg; tmp != NULL; tmp = g->nodes.unreg){
	g->nodes.unreg = tmp->next;
	free(tmp);
    }
}
