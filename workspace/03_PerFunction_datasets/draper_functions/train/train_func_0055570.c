new_popstate_t(void)
{
struct popstate_t *tmp;

tmp = malloc(sizeof(struct popstate_t));

if (tmp == NULL)
	ERROR_ABORT("Unable to malloc\n");


tmp->username=NULL;
tmp->password=NULL;
tmp->num_msgs=-1;

tmp->msg_list=NULL;
tmp->other = NULL;
tmp->size = -1;

return tmp;
}
