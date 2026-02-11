searchFromRemTrie(int cols, double table[][cols], wchar_t *string, int i , int j){
   ARTNode *tmp;
   double value;
   int r = 1;

   tmp = remT->firstNode;
   value = table[i][j] + getPenaltOfChangingPosWithGenEd(i);
   while(tmp != NULL && string != L'\0'){
     if(tmp->label == *string){

        if(tmp->value != DBL_MAX){

            addValueToTable(cols, table, (i+r), j, (value + tmp->value));
        }
        string = string + 1;
        tmp = tmp->nextNode;
        value += getPenaltOfChangingPosWithGenEd(i+r);
        r++;
     }
     else tmp = tmp->rightNode;
   }
   return 0;
}
