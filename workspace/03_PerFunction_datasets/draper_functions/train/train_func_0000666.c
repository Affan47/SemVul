printone(i)
int i;
{
    if (i >= 0) {
	exprintln();
	printch(mbuffer[i].token);
	mvcur(-1,3);
	if (movemap[(unsigned int)(mbuffer[i].token)] == INSMACRO)
	    prints("!= ");
	else
	    prints(" = ");
	prints(mbuffer[i].m_text);
    }
}
