Insert(WordNode *node, char *s)
{
	char *strtemp;
	WordNode *newNode;


	strtemp = (char*) malloc((strlen(s)+1)*sizeof(char));
	if (strtemp==NULL)
		return FAILURE;

	newNode = (WordNode*) malloc(sizeof(WordNode));
	if (newNode==NULL)
		return FAILURE;

	newNode->word = strcpy(strtemp, s);
	newNode->previous = NULL;
	newNode->next = node;

	if(newNode->next){
		newNode->next->previous = newNode;
	}
	return newNode;
}
