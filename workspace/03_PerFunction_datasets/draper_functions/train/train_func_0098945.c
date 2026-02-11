method_24(const int *account, int *weight) {

    int account_buf[10];
    for(int i=0; i<=9; i++) {
	account_buf[i] = account[i];
    }

    if (2 < account_buf[0] && 7 > account_buf[0])
	account_buf[0] = 0;
    if (9 == account_buf[0]) {
	account_buf[0] = 0;
	account_buf[1] = 0;
	account_buf[2] = 0;
	if (0 == account[3])
	    return AccountNumberCheck::ERROR;
    }


    std::string weightString = "";
    for (int i=0; i<10; i++) {
	if (0 == account_buf[i])
	    weightString += "0";
	else {

	    break;
	}
    }
    weightString += "123123123";
    weightString = weightString.substr(0, 9) + "0";

    number2Array(weightString, weight);

    int result = algo05(11, 10, weight, account_buf, 0, 8);
    if (result == account_buf[9])
	return AccountNumberCheck::OK;
    return AccountNumberCheck::ERROR;
}
