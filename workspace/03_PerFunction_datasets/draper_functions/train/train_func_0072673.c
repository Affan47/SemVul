method_A8(const int *account, int *weight) {


    if (9 == account[2])
	return method_51_exception(account,weight);
    number2Array("0007654320", weight);
    if (AccountNumberCheck::OK == algo01(11, weight, false, 10, account))
	return AccountNumberCheck::OK;
    number2Array("0001212120", weight);
    return algo01(10, weight, true, 10, account);
}
