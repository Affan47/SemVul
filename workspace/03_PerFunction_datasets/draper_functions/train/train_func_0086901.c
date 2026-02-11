pushWork(LitVec& work) {
	LitVec* v = new LitVec;
	v->swap(work);
	shared_->workQ.push(v);
	shared_->workSem.up();
}
