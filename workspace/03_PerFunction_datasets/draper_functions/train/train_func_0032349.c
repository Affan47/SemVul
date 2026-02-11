addToTrie(wchar_t *string1, int strLen1, wchar_t *string2, double value){
    TrieNode *tmp;

    if(t->firstNode == NULL){
        t->firstNode = newTrieNode(*string1);
        tmp = t->firstNode;
        if((strLen1-1) == 0)
            tmp->replacement = newEndNode(string2, value);
        else
            addToTrieDepth(tmp, string1+1, strLen1-1, string2, value);
        return 0;
    }

    tmp = t->firstNode;

    while(strLen1 > 0){

        if(strLen1 == 1 && tmp->label == *string1){
           addEndNode(tmp,string2, value);
           return 0;
        }

        else if(tmp->label == *string1 && tmp->nextNode != NULL){
           tmp = tmp->nextNode;
           string1 = string1 + 1;
           strLen1--;
        }

        else if(tmp->label == *string1 && tmp->nextNode == NULL){
           addToTrieDepth(tmp, string1+1,strLen1-1, string2, value);
           return 0;
        }

        else if(tmp->rightNode != NULL)
            tmp = tmp->rightNode;
        else break;
    }

    tmp->rightNode = newTrieNode(*string1);
    tmp = tmp->rightNode;
    if(strLen1 == 1)
       addEndNode(tmp,string2, value);
    else
       addToTrieDepth(tmp, (string1+1),strLen1-1, string2, value);
    return 0;
}
