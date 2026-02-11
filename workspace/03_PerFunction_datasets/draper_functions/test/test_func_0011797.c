dfsVisit(Variable *v, list<Variable*> *order) {
	v->visited=true;
	vector<Constraint*>::iterator it=v->out.begin();
	for(;it!=v->out.end();++it) {
		Constraint *c=*it;
		if(!c->right->visited) {
			dfsVisit(c->right, order);
		}
	}
#ifdef RECTANGLE_OVERLAP_LOGGING
	ofstream f(LOGFILE,ios::app);
	f<<"  order="<<*v<<endl;
#endif
	order->push_front(v);
}
