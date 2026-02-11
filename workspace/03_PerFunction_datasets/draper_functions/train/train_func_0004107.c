deleteAll(fnode *n) {
	if(n!=NULL) {
		fnode* c=n;
		do {
			fnode* d=c;
			c=c->right;
			deleteAll(d->child);
			delete d;
		} while(c!=n);
	}
}
