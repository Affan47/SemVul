method_82(const int *account, int *weight) {
    if (9 == account[2] && 9 == account[3]) {
	number2Array("987654320", weight); weight[0] = 10;
	return algo01(11, weight, false, 10, account);
    } else {
	number2Array("0000654320", weight);
	return algo01(11, weight, false, 10, account);
    }
}
