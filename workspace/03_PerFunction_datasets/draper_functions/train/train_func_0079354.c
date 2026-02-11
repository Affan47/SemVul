method_85(const int *account, int *weight) {

    if (9 == account[2] && 9 == account[3]) {
	number2Array("0087654320", weight);
	return algo02(11, weight, 10, account, 2, 8);
    }


    number2Array("0007654320", weight);
    if (AccountNumberCheck::OK == algo01(11, weight, false, 10, account))
	return AccountNumberCheck::OK;


    number2Array("0000654320", weight);
    if (AccountNumberCheck::OK == algo01(11, weight, false, 10, account))
	return AccountNumberCheck::OK;


    if (account[9] > 6)
	return AccountNumberCheck::ERROR;

    number2Array("0000654320", weight);
    return algo01(7, weight, false, 10, account);
}
