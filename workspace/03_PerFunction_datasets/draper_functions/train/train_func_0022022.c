Run (Record *left, Record *literal, Comparison *c) {

	char *val1, *val2;

	char *left_bits = left->GetBits();
	char *lit_bits = literal->GetBits();


	if (c->operand1 == Left) {
		val1 = left_bits + ((int *) left_bits)[c->whichAtt1 + 1];
	} else {
		val1 = lit_bits + ((int *) lit_bits)[c->whichAtt1 + 1];
	}


	if (c->operand2 == Left) {
		val2 = left_bits + ((int *) left_bits)[c->whichAtt2 + 1];
	} else {
		val2 = lit_bits + ((int *) lit_bits)[c->whichAtt2 + 1];
	}


	int val1Int, val2Int, tempResult;
	double val1Double, val2Double;


	switch (c->attType) {


		case Int:

		val1Int = *((int *) val1);
		val2Int = *((int *) val2);


		switch (c->op) {

			case LessThan:
			return (val1Int < val2Int);
			break;

			case GreaterThan:
			return (val1Int > val2Int);
			break;

			default:
			return (val1Int == val2Int);
			break;
		}
		break;


		case Double:
		val1Double = *((double *) val1);
		val2Double = *((double *) val2);


		switch (c->op) {

			case LessThan:
			return (val1Double < val2Double);
			break;

			case GreaterThan:
			return (val1Double > val2Double);
			break;

			default:
			return (val1Double == val2Double);
			break;
		}
		break;


		default:


		tempResult = strcmp (val1, val2);
		switch (c->op) {

			case LessThan:
			return tempResult < 0;
			break;

			case GreaterThan:
			return tempResult > 0;
			break;

			default:
			return tempResult == 0;
			break;
		}
		break;
	}

}
