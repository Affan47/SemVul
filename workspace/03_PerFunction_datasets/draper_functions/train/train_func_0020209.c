Problem_6_test(){
    Chapter3 chapter3;

    vector<int> input;
    chapter3.Problem_6(input);
    if(!input.empty())
	return false;

    int a[]={5,92,18,-1,9,2,4,0,8,4,0,2,0};
    int correctAnswer[]={-1,0,0,0,2,2,4,4,5,8,9,18,92};
    input.assign(a, a+13);
    chapter3.Problem_6(input);
    if(input.size()!=13)
	return false;
    for(unsigned i=0; i<13; ++i){
	if(input[i]!=correctAnswer[i])
	    return false;
    }
    return true;
}
