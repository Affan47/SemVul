inserts(int inscode, int result, int op1, int op2)
{
    int rvalue=0;

    if (!HaveEnoughSize())  return 0;

    instruction[numberofins][0]=inscode;

    if (inscode == symbolic_const)
    {
       instruction[numberofins][1]=stackno;
        instruction[numberofins][2]=result;
        rvalue=stackno++;
    }
    else if (iconst==inscode)
    {
        instruction[numberofins][1]=stackno;
        instruction[numberofins][2]=result;
        rvalue=stackno++;
    }
    else if (id== inscode)
    {
        instruction[numberofins][1]=stackno;
        instruction[numberofins][2]=result;
        rvalue=stackno++;
    }
    else if (idf== inscode)
    {
        instruction[numberofins][1]=stacknof;
        instruction[numberofins][2]=result;
        rvalue=stacknof++;
    }
    else if (add==inscode||sub==inscode||mult==inscode||divide==inscode
            ||eq==inscode||ne==inscode||ge==inscode
            ||le==inscode||gt==inscode||lt==inscode)
    {
        instruction[numberofins][1]=result;
        instruction[numberofins][2]=op1;
        instruction[numberofins][3]=op2;
        rvalue=result;
        stackno--;
    }
    else if (addf==inscode||subf==inscode||multf==inscode||dividef==inscode
            ||eqf==inscode||nef==inscode||gef==inscode
            ||lef==inscode||gtf==inscode||ltf==inscode)
    {
        instruction[numberofins][1]=result;
        instruction[numberofins][2]=op1;
        instruction[numberofins][3]=op2;
        rvalue=result;
        stacknof--;
    }
    else
        outerror(glno, "unknown error in instruct.insert iconst.");

    instruction[numberofins][4+mx_array_dim]=glno;
    numberofins++;
    return rvalue;
}
