eval(SeVec3d& result) const
{
    const SeExprNode* child0 = child(0);
    const SeExprNode* child1 = child(1);
    SeVec3d a, b;
    child0->eval(a);
    child1->eval(b);
    int index = int(b[0]);

    if (child0->isVec()) {
	switch(index) {
	case 0:  result[0] = a[0]; break;
	case 1:  result[0] = a[1]; break;
	case 2:  result[0] = a[2]; break;
	default: result[0] = 0; break;
	}
    } else {
	switch(index) {
	case 0:
	case 1:
	case 2:  result[0] = a[0]; break;
	default: result[0] = 0; break;
	}
    }
}
