merge(fnode *a, fnode *b){
	if(a==NULL) return b;
	if(b==NULL) return a;
	if(a->data->key > b->data->key) {
		fnode* temp=a;
		a=b;
		b=temp;
	}
	fnode* an=a->right;
	fnode* bp=b->left;
	a->right=b;
	b->left=a;
	an->left=bp;
	bp->right=an;
	return a;
}
