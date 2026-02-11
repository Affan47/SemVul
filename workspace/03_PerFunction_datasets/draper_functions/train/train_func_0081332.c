isInverter(Tree t)
{

    if (gInverter[0] == 0) {
        gInverter[0] = boxSeq(boxPar(boxWire(), boxInt(-1)),boxPrim2(sigMul));
        gInverter[1] = boxSeq(boxPar(boxInt(-1), boxWire()),boxPrim2(sigMul));
        gInverter[2] = boxSeq(boxPar(boxWire(), boxReal(-1.0)),boxPrim2(sigMul));
        gInverter[3] = boxSeq(boxPar(boxReal(-1.0), boxWire()),boxPrim2(sigMul));
        gInverter[4] = boxSeq(boxPar(boxInt(0), boxWire()),boxPrim2(sigSub));
        gInverter[5] = boxSeq(boxPar(boxReal(0.0), boxWire()),boxPrim2(sigSub));
    };


    for (int i=0; i<6; i++) {
        if (t == gInverter[i]) return true;
    }
    return false;
}
