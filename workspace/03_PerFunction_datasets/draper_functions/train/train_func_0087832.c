DoubleType(const int fDoubled, const int fMove, const int fTurn)
{

    if (fDoubled) {


        if (fTurn != fMove)

            return DT_BEAVER;
        else

            return DT_RACCOON;

    }
    return DT_NORMAL;
}
