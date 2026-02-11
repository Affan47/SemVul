method_C1(const int *account, int *weight) {
    if (account[0] != 5)
       return method_17(account,weight);

    number2Array("1212121210", weight);
    int tmp = algo03a(weight, true, account, 0, 9);
    tmp = (tmp - 1) % 11;
    tmp = 10 - tmp;
    if (10 == tmp)
	tmp = 0;
    if ( account[9] == tmp )
	return AccountNumberCheck::OK;
    return AccountNumberCheck::ERROR;
}
