operator<<(std::ostream& os, const Edge& n) {
	os << "Edge ";
	if ( n.isMarked() ) os << " Marked ";
	if ( n.isVisited() ) os << " Visited ";
	return os;
}
