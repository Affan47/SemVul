eval(SeVec3d& result) const
{
    const SeExprNode* child0 = child(0);
    const SeExprNode* child1 = child(1);
    SeVec3d a, b;
    child0->eval(a);
    child1->eval(b);

    if (!_isVec) {
	result[0] = niceMod(a[0], b[0]);
    }
    else {

	if (!child0->isVec()) a[1] = a[2] = a[0];
	if (!child1->isVec()) b[1] = b[2] = b[0];
	result[0] = niceMod(a[0], b[0]);
	result[1] = niceMod(a[1], b[1]);
	result[2] = niceMod(a[2], b[2]);
    }
}
