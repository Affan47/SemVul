method_70(const int *account, int *weight) {
    number2Array("4327654320", weight);
    if (5 == account[3] ||
	(6 == account[3] && 9 == account[4]))
	number2Array("0007654320", weight);
    return algo01(11, weight, false, 10, account);
}
