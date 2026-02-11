Problem_6_test(){
    Chapter5 chapter5;

    unsigned a=0xffffffff;
    unsigned result = chapter5.Problem_6(a);
    if(result!=a)
	return false;


    a=0x69;
    result = chapter5.Problem_6(a);
    if(result!=0x96)
	return false;
    return true;
}
