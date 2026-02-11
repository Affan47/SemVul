gradientAt(long x, int &lapnum)
{


    if (!isValid()) return -100;


    if (x < 0 || x > Duration) return -100;


    if (Laps.count() > 0) {
        int lap=0;
        for (int i=0; i<Laps.count(); i++) {
            if (x>=Laps.at(i).x) lap += 1;
        }
        lapnum = lap;

    } else lapnum = 0;


    while (x < Points.at(leftPoint).x || x > Points.at(rightPoint).x) {
        if (x < Points.at(leftPoint).x) {
            leftPoint--;
            rightPoint--;
        } else if (x > Points.at(rightPoint).x) {
            leftPoint++;
            rightPoint++;
        }
    }
    return Points.at(leftPoint).val;
}
