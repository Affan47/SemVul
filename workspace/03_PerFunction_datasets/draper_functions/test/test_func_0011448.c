insert(double x1, double x2,void* item) {
	AbstractSTRtree::insert(new Interval(min(x1,x2),max(x1, x2)),item);
}
