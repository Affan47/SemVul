insertscalar(int idno, double value)
{
    if (nvars>=maxidnumber)
    {
        outerror(glno,
            "More id than id container can hold, please contact writer.\n");
        return;
    }
    if (Variable.getidnumber(idno)!=-1||getidnumber(idno)!=-1)
    {
        outerror(glno, "id exist.");
        return;
    }

    vararray[nvars]=idname[idno];
    arraytype[nvars]=scalar;
    arraynindex[nvars]=0;
    arrayindex[nvars][0]=0;
    fvalue[nvars]=value;
    nvars++;
}
