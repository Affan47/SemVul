buildBST(BTree *&root, const vector<int> & array, int startPos, int endPos){
    if(startPos==endPos){
	root = NULL;
	return;
    }
    int midPos = (startPos+endPos)/2;
    root = new BTree();
    root->value = array[midPos];
    buildBST(root->left, array, startPos, midPos);
    buildBST(root->right, array, midPos+1, endPos);
}
