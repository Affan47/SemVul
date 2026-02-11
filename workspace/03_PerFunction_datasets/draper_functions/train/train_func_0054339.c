deleteCell(xs, y)
List xs;
Cell y; {
    List result = NIL;
    for(;nonNull(xs);xs=tl(xs)) {
	Cell x = hd(xs);
	if (x != y) {
	    result=cons(x,result);
	}
    }
    return rev(result);
}
