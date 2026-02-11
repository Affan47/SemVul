reset_active_lm(Variable* const v, Variable* const u) {
	for(Cit it=v->out.begin();it!=v->out.end();++it) {
		Constraint *c=*it;
		if(canFollowRight(c,u)) {
			c->lm=0;
			reset_active_lm(c->right,v);
		}
	}
	for(Cit it=v->in.begin();it!=v->in.end();++it) {
		Constraint *c=*it;
		if(canFollowLeft(c,u)) {
			c->lm=0;
			reset_active_lm(c->left,v);
		}
	}
}
