method_26(const int *account, int *weight) {
    number2Array("2765432000", weight);
    if (account[0] == 0 && account[1] == 0) {
	int account_buf[10];
	number2Array(array2Number(account).substr(2) + "00", account_buf);
	return algo01(11, weight, false, 8, account_buf);
    } else {
	return algo01(11, weight, false, 8, account);
    }
}
