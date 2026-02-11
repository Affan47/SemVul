addEndNode(TrieNode *node, wchar_t *string, double value){
    EndNode *endN;
    int i;
    if(node->replacement == NULL){
        node->replacement = newEndNode(string, value);
        return 0;
    }

    endN = node->replacement;
    while(1){
        i = 0;
        while(1){
            if(string[i] == endN->edit[i]){


                 if(string[i] == L'\0'){
                     if(endN->value > value)
                         endN->value = value;
                     return 0;
                 }

                 i++;
            }

            else break;
        }
        if(endN->nextEN == NULL) break;
        else endN = endN->nextEN;
    }
    endN->nextEN = newEndNode(string, value);
    return 0;
}
