list_concat	(list_t *l1,list_t *l2)
{
list_t* tmp=l1;

if(l1 == NULL)
	return l2;
if(l2 == NULL)
	return l1;

while( tmp->next != NULL)
	tmp = tmp->next;

tmp -> next = l2;

return l1;
}
