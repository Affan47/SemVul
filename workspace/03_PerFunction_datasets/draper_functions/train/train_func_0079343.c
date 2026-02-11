recursivePalindrome(LinkedList *forward, LinkedList *&reverseNext, LinkedList *middleBefore, LinkedList *middleAfter){
    if(forward==middleBefore){
	reverseNext = middleAfter->next;
	return (middleBefore->value == middleAfter->value);
    }
    LinkedList *reverse;
    bool preResult = recursivePalindrome(forward->next, reverse, middleBefore, middleAfter);
    if(preResult){
	if(forward->value==reverse->value){
	    reverseNext = reverse->next;
	    return true;
	}
	else
	    return false;
    }
    else
	return false;
}
