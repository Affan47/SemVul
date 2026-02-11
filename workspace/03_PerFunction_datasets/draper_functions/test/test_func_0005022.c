Problem_7_test(){
    Chapter18 chapter18;
    string strArray[] = {"a", "b", "ab", "c", "abcabd", "abcd", "abab"};
    set<string> strSet(strArray, strArray+7);
    string result = chapter18.Problem_7(strSet);
    if(result!="abab")
	return false;
    return true;
}
