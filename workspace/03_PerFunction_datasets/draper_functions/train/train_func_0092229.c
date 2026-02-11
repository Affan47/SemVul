Init(int number)
{
    numberWinding = (number < 1) ? 4 : number;
    if (windings)
        delete [] windings;
    if (windingAngles)
        delete [] windingAngles;

    windings = new eCoord[numberWinding]();
    windingAngles = new REAL[numberWinding];

    ComputeWinding();
    SnapWinding();
    ComputeAngles();
}
