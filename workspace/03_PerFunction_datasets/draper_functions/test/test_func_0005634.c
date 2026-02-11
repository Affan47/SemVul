ClearVariableTree(VARIABLE *t)
{
    if (t == NULL)
	return;

    ClearVariableTree(t->left);
    ClearVariableTree(t->right);
    DestroyVariable(t);
    FreeMemory(t);
}
