Get_Time (Object time) {
    if (EQ(time, Sym_Now))
        return CurrentTime;
    return (Time)Get_Long (time);
}
