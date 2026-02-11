Problem_1_test(){
    Chapter10 chapter10;
    int A[]={1,3,9,19,0,0,0,0,0,0};
    int B[]={2,3,9,11,13};
    int correctResult[]={1,2,3,3,9,9,11,13,19};
    chapter10.Problem_1(A, 4, B, 5);
    for(size_t i=0; i<9; ++i){
	if(A[i]!=correctResult[i])
	    return false;
    }
    return true;
}
