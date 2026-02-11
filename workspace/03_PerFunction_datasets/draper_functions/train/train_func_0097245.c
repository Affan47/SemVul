prep(bool wantVec)
{


    bool valid=true;
    std::vector<SeExprNode*>::iterator iter;
    _isVec = 0;
    for (iter = _children.begin(); iter != _children.end(); iter++) {
	SeExprNode* child = *iter;
	if (!child->prep(wantVec)) valid=false;
	if (child->isVec()) _isVec = 1;
    }
    return valid;
}
