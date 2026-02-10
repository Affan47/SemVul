method_D4(const int *account, int *weight) {

    if (account[0] == 0)
	return AccountNumberCheck::ERROR;

    number2Array("2121212120", weight);
    int result  = algo03(10, weight, true, account, 0, 8);

    result	+= 29;

    result	= (1000 - result) % 10;

    if (account[9] == result)
	return AccountNumberCheck::OK;
    else
	return AccountNumberCheck::ERROR;
}
