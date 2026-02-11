_DBMathOperator (char *str,DBInt *len)

	{
	const char *operStr [] = { " + "," - ", " * ", " % "," / ", " ^ ", " ** ",
								" && "," || "," < "," <= "," == "," != "," <> "," >= "," > ", (char *) NULL };
	DBInt operCodes [] = { 	DBMathOperatorAdd,
									DBMathOperatorSub,
									DBMathOperatorMul,
									DBMathOperatorMod,
									DBMathOperatorDiv,
									DBMathOperatorExp,
									DBMathOperatorExp,
									DBMathOperatorAnd,
									DBMathOperatorOr,
									DBMathOperatorSml,
									DBMathOperatorSml | DBMathOperatorEqu,
									DBMathOperatorEqu,
									DBMathOperatorSml | DBMathOperatorGrt,
									DBMathOperatorSml | DBMathOperatorGrt,
									DBMathOperatorGrt | DBMathOperatorEqu,
									DBMathOperatorGrt }, oper;
	DBInt operLen [] = { 3,3,3,3,3,3,4,4,4,3,4,4,4,4,4,3 };

	if ((oper = CMoptLookup (operStr,str,false)) == DBFault) return (DBFault);

	*len = operLen [oper];
	return (operCodes [oper]);
	}
