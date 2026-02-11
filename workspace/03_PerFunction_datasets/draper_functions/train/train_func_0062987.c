P_Oddp (Object x) {
    Object tmp;
    tmp = P_Evenp (x);
    return EQ(tmp,True) ? False : True;
}
