Problem_2_test(){
    Chapter2 chapter2;

    LinkedList *input1=NULL;
    if(chapter2.Problem_2(input1, 6)!=NULL)
	return false;


    int a[]={1};
    LinkedList *input2 = LinkedList::createList(a, a+1);
    if(chapter2.Problem_2(input2, 4)!=NULL)
	return false;


    int b[]={1,2,3,4,5,6,7,8,9};
    LinkedList *input3 = LinkedList::createList(b, b+9);
    for(int i=1; i<=9; ++i){
	if(chapter2.Problem_2(input3,i)->value!=10-i)
	    return false;
    }
    return true;
}
