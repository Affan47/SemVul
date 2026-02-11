togo(Node *node)
{
	Arc *la, *a;


	la = 0;
	for(a = node->prereqs; a; la = a, a = a->next)
		if(a->flag&TOGO){
			if(a == node->prereqs)
				node->prereqs = a->next;
			else
				la->next = a->next, a = la;
		}
}
