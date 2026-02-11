check_array_qr(Quadruple *qpt, int entry)
{
    int i;

    for (i = 0; i < 4; i++){
	if(check_array_operand(qpt->op[i], entry)){
	    return TRUE;
	}
    }
    return FALSE;
}
