NewNode(NODE * Child)
{
    NODE *N;

    N = malloc(sizeof(NODE));
    if (N == NULL)
	return NULL;

    memset(N, 0, sizeof(NODE));
    N->Token = Token;
    N->Operator = Operator;

    if (Child != NULL) {
	N->Children = 1;
	N->Child = malloc(sizeof(NODE *));
	N->Child[0] = Child;
    }

    return N;

}
