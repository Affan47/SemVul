what() const throw (){
    ostringstream o;
    if (config.prefixtimestamp()) {
	Timestamp tm;
	o << tm.desc() << ' ';
    }
    o << pthread_self() << " ERROR: " << desc;
    return (o.str().c_str());
}
