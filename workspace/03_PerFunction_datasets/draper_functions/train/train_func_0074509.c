btdelete(void **uroot,void *key,CMP)
#else
int btdelete(uroot,key,cmp)
void **uroot;
void *key;
int (*cmp)();
#endif
{
	node_t **root=(node_t**)uroot;
	if (*root == NULL)
		return -1;
	search(root,*root,key,NULL,cmp,BT_DEL,NULL);
	return 0;
}
