zTBTreeSetChild(zTBTreeNode* p,zTBTreeNode* c){

	if(c->parent != NULL){
		if(c->parent->child == c){
			c->parent->child = c->rsib;

		}
		else{

			c->lsib->rsib = c->rsib;
		}

		if(c->rsib != NULL){
			c->rsib->lsib = c->lsib;
		}
		c->parent->children--;
		if(c->parent->children < 0){
			zDie("zTBTreeLiveNode children count is off\n");
		}
	}
	c->lsib = NULL;
	c->rsib = NULL;

	if(p->child != NULL){
		c->rsib = p->child;
		p->child->lsib = c;
	}
	p->child = c;
	c->parent = p;
	p->children++;
}
