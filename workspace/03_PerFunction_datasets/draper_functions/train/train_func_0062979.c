edgeattr(Type t)
{
    string s;


    if (t->nature()==kInt) {
        s += " color=\"blue\"";
    } else {
        s += " color=\"red\"";
    }


    if (t->vectorability()==kVect && t->variability()==kSamp) {
        s += " style=\"bold\"";
    }
    return s;
}
